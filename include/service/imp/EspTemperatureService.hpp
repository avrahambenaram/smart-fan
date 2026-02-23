#pragma once

#include "service/FanService.hpp"
#include "service/TemperatureReader.hpp"
#include "service/TemperatureService.hpp"
#include "service/TemperatureStorage.hpp"

#include <Preferences.h>
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <vector>

class EspTemperatureService : public TemperatureService {
public:
  EspTemperatureService(TemperatureStorage &storage, TemperatureReader &reader,
                        FanService &fan);
  void setup();
  bool isEnabled() override;
  void enable() override;
  void disable() override;
  void toggle() override;
  void setPoweringTemperature(float temp) override;
  float getPoweringTemperature() override;

private:
  bool enabled;
  float poweringTemperature;
  TimerHandle_t timer;
  TemperatureStorage &storage;
  TemperatureReader &reader;
  FanService &fan;

  void saveConfig();
  static void readTimer(TimerHandle_t xTimer);
};
