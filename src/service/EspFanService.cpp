#include "service/imp/EspFanService.hpp"
#include "DBG.h"

bool EspFanService::isPowered() {
  return powered;
}

void EspFanService::toggle() {
  if (powered)
    powerOff();
  else
    powerOn();
}

void EspFanService::powerOn() {
  DBG("[Fan Service] Powering on...");
  powered = true;
  for (auto o : observers) {
    o->onPowerOn();
  }
}

void EspFanService::powerOff() {
  DBG("[Fan Service] Powering off...");
  powered = false;
  for (auto o : observers) {
    o->onPowerOff();
  }
}

void EspFanService::registerObserver(FanObserver *observer) {
  observers.push_back(observer);
}

void EspFanService::unregisterObserver(FanObserver *observer) {
  observers.erase(std::remove(observers.begin(), observers.end(), observer),
                  observers.end());
}
