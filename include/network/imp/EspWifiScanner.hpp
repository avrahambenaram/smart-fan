#pragma once

#include "network/WifiScanner.hpp"
#include "network/dto/WifiNetworkDto.hpp"

class EspWifiScanner : public WifiScanner {
public:
  EspWifiScanner(WifiNetworkListPtr networks, WifiNetworkPtr statusNetwork);
  void start();
  void stop();

private:
  bool running{false};
  WifiNetworkPtr statusNetwork;
  TaskHandle_t scanTaskHandle;
  static void scanTask(void *param);
  void processScan();
  WifiNetworkDto processScanItem(int i);
};
