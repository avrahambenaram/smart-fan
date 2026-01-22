#pragma once

#include "network/dto/WifiNetworkDto.hpp"

class WifiSTAObserver {
public:
  virtual void onConnecting(const WifiNetworkDto) {};
  virtual void onConnect(const WifiNetworkDto) {};
  virtual void onError(const WifiNetworkDto) {};
};
