#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "network/WifiObserver.hpp"
#include "network/WifiSTA.hpp"
#include "network/WifiStorage.hpp"

class Reconnector : public WifiObserver {
public:
  Reconnector(WifiStorage &storage, WifiSTA &sta);
  void onConnect() override;
  void onDisconnect() override;

private:
  WifiStorage &wifiStorage;
  WifiSTA &wifiSTA;
  TimerHandle_t timer;

  static void reconnectTimer(TimerHandle_t xTimer);
};
