#pragma once

#include "network/WifiSTAObserver.hpp"
#include "network/dto/WifiConnectDto.hpp"
#include <vector>

class WifiSTA {
public:
  void reconnect();
  bool isConnected();
  void connect(WifiConnectDto wifiConnectDto);

private:
  void connectDHCP(WifiConnectDto connectCmd);
  void connectStatic(WifiConnectDto connectCmd);
  void connect(String ssid, String pass);
};
