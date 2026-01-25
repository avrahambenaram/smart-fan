#pragma once

#include "service/FanService.hpp"
#include "service/TemperatureObserver.hpp"
#include "Config.h"

class FanTemperatureObserver : public TemperatureObserver {
public:
  float poweringTemperature{TEMPERATURE_POWERING};
  bool enabled{false};

  FanTemperatureObserver(FanService &fanService) : fanService(fanService) {};
  void onRead(float temperature) override;

private:
  FanService &fanService;
};
