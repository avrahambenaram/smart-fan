#pragma once

#include "network/WifiObserver.hpp"
#include "network/WifiReconnector.hpp"

class Reconnector : public WifiObserver {
public:
  Reconnector(WifiReconnector &wifiReconnector)
    : wifiReconnector(wifiReconnector) {};
  void onConnect() override;
  void onDisconnect() override;

private:
  WifiReconnector &wifiReconnector;
};
