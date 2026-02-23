#include <ArduinoJson.h>
#include "web/TemperatureController.hpp"

void TemperatureController::setup() {
  server.on("/api/temperature/status", HTTP_GET, [this](AsyncWebServerRequest *request) { handleStatus(*this, request); });
  server.on("/api/temperature/update", HTTP_PATCH, [this](AsyncWebServerRequest *request) { handleUpdate(*this, request); });
}

void TemperatureController::handleStatus(TemperatureController &temperatureController, AsyncWebServerRequest *request) {
  JsonDocument doc;
  doc["enabled"] = temperatureController.temperatureService.isEnabled();
  doc["temperature"] = temperatureController.temperatureService.getPoweringTemperature();
  String json;
  serializeJson(doc, json);
  auto *res = request->beginResponse(200, "application/json", json);
  res->addHeader("Cache-Control", "no-store");
  res->addHeader("Connection", "close");
  request->send(res);
}

void TemperatureController::handleUpdate(TemperatureController &temperatureController, AsyncWebServerRequest *request) {
  // TODO: Implement method
}
