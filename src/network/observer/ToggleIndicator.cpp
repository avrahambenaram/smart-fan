#include "network/observer/ToggleIndicator.hpp"
#include "Arduino.h"
#include "Config.h"

ToggleIndicator::ToggleIndicator() {
  pinMode(INDICATOR_PIN, OUTPUT);
  digitalWrite(INDICATOR_PIN, LOW);
}

void ToggleIndicator::onConnect() { digitalWrite(INDICATOR_PIN, HIGH); }

void ToggleIndicator::onDisconnect() { digitalWrite(INDICATOR_PIN, LOW); }
