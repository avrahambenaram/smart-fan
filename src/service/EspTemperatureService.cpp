#include "service/imp/EspTemperatureService.hpp"
#include "Config.h"
#include "DBG.h"

EspTemperatureService::EspTemperatureService(Preferences &prefs,
                                             TemperatureReader &reader,
                                             FanService &fan)
    : prefs(prefs), reader(reader), fan(fan) {
  timer = xTimerCreate("temp-service", pdMS_TO_TICKS(TEMPERATURE_READ_TIMER),
                       pdTRUE, this, EspTemperatureService::readTimer);
}

void EspTemperatureService::setup() {
  auto active = prefs.getBool("temperature", true);
  enabled = active;
  if (active)
    xTimerStart(timer, 0);

  auto temp = prefs.getFloat("powering-temp", TEMPERATURE_POWERING);
  poweringTemperature = temp;
}

void EspTemperatureService::enable() {
  DBG("[TemperatureService] Enabling...");
  enabled = true;
  prefs.putBool("temperature", enabled);
}

void EspTemperatureService::disable() {
  DBG("[TemperatureService] Disabling...");
  enabled = false;
  prefs.putBool("temperature", enabled);
}

void EspTemperatureService::toggle() {
  if (enabled)
    disable();
  else
    enable();
}

void EspTemperatureService::setPoweringTemperature(float temp) {
  poweringTemperature = temp;
  prefs.putFloat("powering-temp", poweringTemperature);
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
