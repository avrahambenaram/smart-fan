#pragma once

#include <WebServer.h>

class WebController {
public:
  WebController(WebServer &server) : server(server) {}
  void setup();

private:
  WebServer &server;

  static void handleFile(WebController &webController);
  static String getContentType(String filename);
};
