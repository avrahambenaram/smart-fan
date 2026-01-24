#pragma once

#include "service/FanService.hpp"
#include <WebServer.h>

class FanController {
public:
  FanController(WebServer &server, FanService &fanService)
    : server(server), fanService(fanService) {}
  void setup();

private:
  FanService &fanService;
  WebServer &server;

  static void handleStatus(FanController &fanController);
  static void handleToggle(FanController &fanController);
};
