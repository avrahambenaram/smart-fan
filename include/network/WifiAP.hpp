#pragma once

#include "network/dto/WifiNetworkDto.hpp"
#include <DNSServer.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <cstdint>

class WifiAP {
public:
  void start();
  void stop();
  void loop();
  uint16_t countConnected();

private:
  DNSServer dns;
  const byte DNS_PORT{53};

  IPAddress apIP{192, 168, 4, 1};
  IPAddress gateway{192, 168, 4, 1};
  IPAddress subnet{255, 255, 255, 0};

  bool running;
};
