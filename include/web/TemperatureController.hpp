#pragma once

#include "service/TemperatureService.hpp"
#include <ESPAsyncWebServer.h>

class TemperatureController {
public:
  TemperatureController(AsyncWebServer &server, TemperatureService &temperatureService) : server(server), temperatureService(temperatureService) {}
  void setup();

private:
  AsyncWebServer &server;
  TemperatureService &temperatureService;

  static void handleStatus(TemperatureController &temperatureController, AsyncWebServerRequest *request);
  static void handleUpdate(TemperatureController &temperatureController, AsyncWebServerRequest *request);
};
