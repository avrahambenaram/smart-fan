#include <Arduino.h>

#include "service/imp/EspFanService.hpp"
#include "Config.h"
#include "DBG.h"

EspFanService::EspFanService() {
  pinMode(RELAY_PIN, OUTPUT);
}

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
  digitalWrite(RELAY_PIN, powered);
}

void EspFanService::powerOff() {
  DBG("[Fan Service] Powering off...");
  powered = false;
  digitalWrite(RELAY_PIN, powered);
}
