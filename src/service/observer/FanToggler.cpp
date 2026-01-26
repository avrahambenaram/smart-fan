#include <Arduino.h>

#include "service/observer/FanToggler.hpp"
#include "Config.h"

FanToggler::FanToggler() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void FanToggler::onPowerOn() {
  digitalWrite(RELAY_PIN, HIGH);
}

void FanToggler::onPowerOff() {
  digitalWrite(RELAY_PIN, LOW);
}
