#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

#include "network/dto/WifiNetworkDto.hpp"
#include "web/SetupController.hpp"

void SetupController::setup() {
  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS mount failed");
    return;
  }
  server.onNotFound([this]() { handleFile(*this); });
  server.on("/wifi-setup", HTTP_POST, [this]() { handleSetup(*this); });
  server.on("/wifi-list", HTTP_GET, [this]() { handleList(*this); });
  server.on("/wifi-status", HTTP_GET, [this]() { handleStatus(*this); });
}

void SetupController::start() {
  if (running)
    return;
  server.begin();
  running = true;
}

void SetupController::stop() {
  if (!running)
    return;
  server.stop();
  running = false;
}

void SetupController::loop() {
  if (!running)
    return;
  server.handleClient();
}

void SetupController::handleSetup(SetupController &setupServer) {
  if (setupServer.server.method() != HTTP_POST) {
    setupServer.server.send(405, "text/plain", "Method Not Allowed");
    return;
  }

  String body = setupServer.server.arg("plain");
  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, body);
  if (err)
    return;

  String ssid = doc["ssid"];
  String pass = doc["pass"];
  String ip = doc["ip"];
  String gateway = doc["gateway"];
  String subnet = doc["subnet"];
  WifiConnectDto cmd{ssid, pass, ip, gateway, subnet};
  setupServer.server.sendHeader("Cache-Control", "no-store");
  setupServer.server.sendHeader("Connection", "close");
  setupServer.server.send(200);
  setupServer.wifiStorage.save(cmd);
  setupServer.wifiSTA.connect(cmd);
}

void SetupController::handleList(SetupController &setupServer) {
  JsonDocument doc;
  JsonArray array = doc.to<JsonArray>();

  for (auto network : *setupServer.networks) {
    JsonObject o = array.add<JsonObject>();
    o["ssid"] = network.ssid;
    o["secure"] = network.secure;
    o["status"] = static_cast<int>(network.status);
    o["rssi"] = network.rssi;
  }
  String json;
  serializeJson(doc, json);
  setupServer.server.sendHeader("Cache-Control", "no-store");
  setupServer.server.sendHeader("Connection", "close");
  setupServer.server.send(200, "application/json", json);
}

void SetupController::handleStatus(SetupController &setupServer) {
  JsonDocument doc;
  doc["ssid"] = setupServer.statusNetwork->ssid;
  doc["status"] = static_cast<int>(setupServer.statusNetwork->status);
  doc["rssi"] = setupServer.statusNetwork->rssi;
  String json;
  serializeJson(doc, json);
  setupServer.server.sendHeader("Cache-Control", "no-store");
  setupServer.server.sendHeader("Connection", "close");
  setupServer.server.send(200, "application/json", json);
}

void SetupController::handleFile(SetupController &setupServer) {
  String path = setupServer.server.uri();
  if (path == "/")
    path = "/index.html";
  if (!LittleFS.exists(path))
    path = "/index.html";

  File file = LittleFS.open(path, "r");

  // Determine content type
  String contentType = getContentType(path);

  setupServer.server.sendHeader("Cache-Control", "no-store");
  setupServer.server.sendHeader("Connection", "close");
  setupServer.server.streamFile(file, contentType);
  file.close();
}

String SetupController::getContentType(String filename) {
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
