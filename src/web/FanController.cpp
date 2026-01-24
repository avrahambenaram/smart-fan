#include <ArduinoJson.h>
#include "web/FanController.hpp"

void FanController::setup() {
  server.on("/api/fan/status", HTTP_GET, [this]() { handleStatus(*this); });
  server.on("/api/fan/toggle", HTTP_POST, [this]() { handleToggle(*this); });
}

void FanController::handleStatus(FanController &fanController) {
  JsonDocument doc;
  doc["status"] = fanController.fanService.isPowered();
  String json;
  serializeJson(doc, json);
  fanController.server.sendHeader("Cache-Control", "no-store");
  fanController.server.sendHeader("Connection", "close");
  fanController.server.send(200, "application/json", json);
}

void FanController::handleToggle(FanController &fanController) {
  fanController.fanService.toggle();
  fanController.server.send(200);
}
