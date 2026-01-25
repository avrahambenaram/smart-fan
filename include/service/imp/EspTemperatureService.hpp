#pragma once

#include "service/TemperatureService.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <vector>

class EspTemperatureService : public TemperatureService {
public:
  EspTemperatureService();
  float get() override;
  void registerObserver(TemperatureObserver *observer) override;
  void unregisterObserver(TemperatureObserver *observer) override;

private:
  std::vector<TemperatureObserver *> observers;
  TimerHandle_t timer;

  static void read(TimerHandle_t xTimer);
};
