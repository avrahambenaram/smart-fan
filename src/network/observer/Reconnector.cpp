#include "network/observer/Reconnector.hpp"
#include "Config.h"
#include "DBG.h"

Reconnector::Reconnector(WifiStorage &storage, WifiSTA &sta)
    : wifiStorage(storage), wifiSTA(sta) {
  timer = xTimerCreate("WifiReconnector", pdMS_TO_TICKS(WIFI_RECONNECT_TIMER),
                       pdTRUE, this, Reconnector::reconnectTimer);
}

void Reconnector::onConnect() { xTimerStop(timer, 0); }

void Reconnector::onDisconnect() { xTimerStart(timer, 0); }

void Reconnector::reconnectTimer(TimerHandle_t xTimer) {
  auto *reconnect = static_cast<Reconnector *>(pvTimerGetTimerID(xTimer));
  auto dto = reconnect->wifiStorage.restore();
  if (!dto)
    return;

  DBG("[Reconnect Observer] Reconnecting to wifi");
  reconnect->wifiSTA.connect(*dto);
}
