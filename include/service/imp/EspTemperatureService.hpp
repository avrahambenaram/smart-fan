#pragma once

#include "service/TemperatureService.hpp"
#include "service/TemperatureReader.hpp"
#include "service/FanService.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <vector>
#include <Preferences.h>

class EspTemperatureService : public TemperatureService {
public:
  EspTemperatureService(Preferences &prefs, TemperatureReader &reader, FanService &fan);
  void setup();
  void enable() override;
  void disable() override;
  void toggle() override;
  void setPoweringTemperature(float temp) override;

private:
  bool enabled;
  float poweringTemperature;
  TimerHandle_t timer;
  Preferences &prefs;
  TemperatureReader &reader;
  FanService &fan;

  static void readTimer(TimerHandle_t xTimer);
};
