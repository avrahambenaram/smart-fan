#include "network/WifiManager.hpp"

#include "Arduino.h"
#include "WiFi.h"
#include <memory>

void WifiManager::setup() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.setSleep(false);
}

void WifiManager::start() {
  auto dto = storage.restore();
  ap.start();
  scanner.start();

  if (dto)
    sta.connect(*dto);
}

void WifiManager::stop() {
  ap.stop();
  scanner.stop();
}
