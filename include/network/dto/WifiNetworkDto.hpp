#pragma once

#include <Arduino.h>
#include <memory>
#include <vector>

enum class WifiStatus {
  WIFI_NONE = 0,
  WIFI_CONNECTING,
  WIFI_CONNECTED,
  WIFI_ERROR
};

struct WifiNetwork {
  String ssid;
  bool secure;       // true = needs password
  WifiStatus status; // 0..3
  int32_t rssi;
};

using NetworkPtr = std::shared_ptr<WifiNetwork>;
using NetworkList = std::vector<WifiNetwork>;
using NetworkListPtr = std::shared_ptr<NetworkList>;
