#include "service/imp/EspTemperatureService.hpp"
#include "Config.h"
#include "DBG.h"

EspTemperatureService::EspTemperatureService(TemperatureStorage &storage,
                                             TemperatureReader &reader,
                                             FanService &fan)
    : storage(storage), reader(reader), fan(fan) {
  timer = xTimerCreate("temp-service", pdMS_TO_TICKS(TEMPERATURE_READ_TIMER),
                       pdTRUE, this, EspTemperatureService::readTimer);
}

void EspTemperatureService::setup() {
  auto dto = storage.restore();
  poweringTemperature = dto.poweringTemperature;
  enabled = dto.enabled;
  if (enabled)
    xTimerStart(timer, 0);
}

bool EspTemperatureService::isEnabled() { return enabled; }

void EspTemperatureService::enable() {
  DBG("[TemperatureService] Enabling...");
  enabled = true;
  saveConfig();
}

void EspTemperatureService::disable() {
  DBG("[TemperatureService] Disabling...");
  enabled = false;
  saveConfig();
}

void EspTemperatureService::toggle() {
  if (enabled)
    disable();
  else
    enable();
}

void EspTemperatureService::setPoweringTemperature(float temp) {
  poweringTemperature = temp;
  saveConfig();
}

float EspTemperatureService::getPoweringTemperature() {
  return poweringTemperature;
}

void EspTemperatureService::saveConfig() {
  TemperatureDto dto{enabled, poweringTemperature};
  storage.save(dto);
}

void EspTemperatureService::readTimer(TimerHandle_t xTimer) {
  auto *service =
      static_cast<EspTemperatureService *>(pvTimerGetTimerID(xTimer));
  auto temp = service->reader.read();
  if (temp >= service->poweringTemperature)
    service->fan.powerOn();
  else
    service->fan.powerOff();
}
