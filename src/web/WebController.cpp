#include <LittleFS.h>

#include "web/WebController.hpp"

void WebController::setup() {
  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS mount failed");
    return;
  }
  server.onNotFound([this]() { handleFile(*this); });
}

void WebController::handleFile(WebController &webController) {
  String path = webController.server.uri();
  if (path == "/")
    path = "/index.html";
  if (!LittleFS.exists(path))
    path = "/index.html";

  File file = LittleFS.open(path, "r");

  // Determine content type
  String contentType = getContentType(path);

  webController.server.sendHeader("Cache-Control", "no-store");
  webController.server.sendHeader("Connection", "close");
  webController.server.streamFile(file, contentType);
  file.close();
}

String WebController::getContentType(String filename) {
  if (filename.endsWith(".html"))
    return "text/html";
  if (filename.endsWith(".css"))
    return "text/css";
  if (filename.endsWith(".js"))
    return "application/javascript";
  if (filename.endsWith(".png"))
    return "image/png";
  if (filename.endsWith(".jpg"))
    return "image/jpeg";
  if (filename.endsWith(".svg"))
    return "image/svg+xml";
  if (filename.endsWith(".ico"))
    return "image/x-icon";
  return "text/plain";
}
