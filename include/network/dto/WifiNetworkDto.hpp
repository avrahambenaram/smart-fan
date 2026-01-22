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

struct WifiNetworkDto {
  String ssid;
  bool secure;       // true = needs password
  WifiStatus status; // 0..3
  int32_t rssi;
};

using NetworkPtr = std::shared_ptr<WifiNetworkDto>;
using NetworkList = std::vector<WifiNetworkDto>;
using NetworkListPtr = std::shared_ptr<NetworkList>;
