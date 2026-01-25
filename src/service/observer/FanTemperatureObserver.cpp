#include "service/observer/FanTemperatureObserver.hpp"

void FanTemperatureObserver::onRead(float temperature) {
  if (!enabled)
    return;

  if (temperature >= poweringTemperature)
    fanService.powerOn();
  else
    fanService.powerOff();
}
