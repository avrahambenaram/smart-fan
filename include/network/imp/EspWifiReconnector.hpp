#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>

#include "network/WifiStorage.hpp"
#include "network/WifiSTA.hpp"
#include "network/WifiReconnector.hpp"

class EspWifiReconnector : public WifiReconnector {
public:
  EspWifiReconnector(WifiStorage &wifiStorage, WifiSTA &wifiSTA);
  void start() override;
  void stop() override;

private:
  WifiStorage &wifiStorage;
  WifiSTA &wifiSTA;
  TimerHandle_t timer;

  static void reconnectTimer(TimerHandle_t xTimer);
};
