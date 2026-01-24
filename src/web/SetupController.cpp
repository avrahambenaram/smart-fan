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
  server.on("/api/wifi", HTTP_GET, [this]() { handleList(*this); });
  server.on("/api/wifi/status", HTTP_GET, [this]() { handleStatus(*this); });
  server.on("/api/wifi/setup", HTTP_POST, [this]() { handleSetup(*this); });
}

void SetupController::handleSetup(SetupController &setupController) {
  if (setupController.server.method() != HTTP_POST) {
    setupController.server.send(405, "text/plain", "Method Not Allowed");
    return;
  }

  String body = setupController.server.arg("plain");
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
  setupController.server.sendHeader("Cache-Control", "no-store");
  setupController.server.sendHeader("Connection", "close");
  setupController.server.send(200);
  setupController.wifiStorage.save(cmd);
  setupController.wifiSTA.connect(cmd);
}

void SetupController::handleList(SetupController &setupController) {
  JsonDocument doc;
  JsonArray array = doc.to<JsonArray>();

  for (auto network : *setupController.networks) {
    JsonObject o = array.add<JsonObject>();
    o["ssid"] = network.ssid;
    o["secure"] = network.secure;
    o["status"] = static_cast<int>(network.status);
    o["rssi"] = network.rssi;
  }
  String json;
  serializeJson(doc, json);
  setupController.server.sendHeader("Cache-Control", "no-store");
  setupController.server.sendHeader("Connection", "close");
  setupController.server.send(200, "application/json", json);
}

void SetupController::handleStatus(SetupController &setupController) {
  JsonDocument doc;
  doc["ssid"] = setupController.statusNetwork->ssid;
  doc["status"] = static_cast<int>(setupController.statusNetwork->status);
  doc["rssi"] = setupController.statusNetwork->rssi;
  String json;
  serializeJson(doc, json);
  setupController.server.sendHeader("Cache-Control", "no-store");
  setupController.server.sendHeader("Connection", "close");
  setupController.server.send(200, "application/json", json);
}
