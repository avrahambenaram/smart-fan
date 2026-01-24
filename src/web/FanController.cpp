#include <ArduinoJson.h>
#include "web/FanController.hpp"

void FanController::setup() {
  server.on("/api/fan/status", HTTP_GET, [this](AsyncWebServerRequest *request) { handleStatus(*this, request); });
  server.on("/api/fan/toggle", HTTP_POST, [this](AsyncWebServerRequest *request) { handleToggle(*this, request); });
}

void FanController::handleStatus(FanController &fanController, AsyncWebServerRequest *request) {
  JsonDocument doc;
  doc["status"] = fanController.fanService.isPowered();
  String json;
  serializeJson(doc, json);
  auto *res = request->beginResponse(200, "application/json", json);
  res->addHeader("Cache-Control", "no-store");
  res->addHeader("Connection", "close");
  request->send(res);
}

void FanController::handleToggle(FanController &fanController, AsyncWebServerRequest *request) {
  fanController.fanService.toggle();
  request->send(200);
}
