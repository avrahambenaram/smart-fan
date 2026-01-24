#pragma once

#include "Arduino.h"
#include "WifiAP.hpp"
#include "freertos/FreeRTOS.h"
#include "network/WifiObserver.hpp"
#include "network/dto/WifiConnectDto.hpp"
#include <WiFi.h>
#include <cstdint>
#include <memory>

class WifiSTA {
public:
  virtual void connect(WifiConnectDto connectCmd) = 0;
  virtual void reconnect() = 0;
  virtual bool isConnected() = 0;
  virtual void registerObserver(WifiObserver *observer) = 0;
  virtual void unregisterObserver(WifiObserver *observer) = 0;

  virtual ~WifiSTA() = default;
};
