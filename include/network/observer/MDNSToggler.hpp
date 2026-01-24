#pragma once

#include "network/WifiObserver.hpp"

class MDNSToggler : public WifiObserver {
public:
  void onConnect() override;
  void onDisconnect() override;
};
