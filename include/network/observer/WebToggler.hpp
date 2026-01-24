#pragma once

#include "network/WifiObserver.hpp"
#include "web/SetupServer.hpp"

class WebToggler : public WifiObserver {
public:
  WebToggler(SetupServer &setupServer);
  void onConnect() override;
  void onDisconnect() override;

private:
  SetupServer &setupServer;
};
