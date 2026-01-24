#pragma once

#include "Arduino.h"
#include "network/WifiSTA.hpp"
#include "network/dto/WifiConnectDto.hpp"
#include "network/dto/WifiNetworkDto.hpp"
#include <WiFi.h>
#include <cstdint>
#include <memory>

class EspWifiSTA : public WifiSTA {
public:
  EspWifiSTA(WifiNetworkPtr statusNetwork);
  void connect(WifiConnectDto connectCmd) override;
  void reconnect() override;
  bool isConnected() override;
  void registerObserver(WifiObserver *observer) override;
  void unregisterObserver(WifiObserver *observer) override;

private:
  std::vector<WifiObserver *> observers;
  WifiNetworkPtr statusNetwork;
  static EspWifiSTA *instance;

  void connectDHCP(WifiConnectDto connectCmd);
  void connectStatic(WifiConnectDto connectCmd);
  void connect(String ssid, String pass);
  static void onWiFiEvent(WiFiEvent_t event);
};
