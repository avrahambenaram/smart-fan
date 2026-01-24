#include <Arduino.h>

#include "service/imp/EspFanService.hpp"
#include "Config.h"

EspFanService::EspFanService() {
  pinMode(RELAY_PIN, OUTPUT);
}

bool EspFanService::isPowered() {
  return powered;
}

void EspFanService::toggle() {
  powered = !powered;
  digitalWrite(RELAY_PIN, powered);
}

void EspFanService::powerOn() {
  powered = true;
  digitalWrite(RELAY_PIN, powered);
}

void EspFanService::powerOff() {
  powered = false;
  digitalWrite(RELAY_PIN, powered);
}
