#pragma once

#include "service/FanService.hpp"
#include <ESPAsyncWebServer.h>

class FanController {
public:
  FanController(AsyncWebServer &server, FanService &fanService)
    : server(server), fanService(fanService) {}
  void setup();

private:
  FanService &fanService;
  AsyncWebServer &server;

  static void handleStatus(FanController &fanController, AsyncWebServerRequest *request);
  static void handleToggle(FanController &fanController, AsyncWebServerRequest *request);
};
