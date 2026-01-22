#pragma once

#include <WiFi.h>

struct WifiConnectDto {
  const String ssid;
  const String pass;
  const String ip;
  const String gateway;
  const String subnet;

  bool isDHCP() const { return ip == ""; }
};
