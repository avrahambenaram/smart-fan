#pragma once

#include "network/WifiObserver.hpp"

class ToggleIndicator : public WifiObserver {
public:
  ToggleIndicator();
  void onConnect() override;
  void onDisconnect() override;
};
