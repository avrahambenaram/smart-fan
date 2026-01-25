#include "service/imp/EspTemperatureService.hpp"
#include "Config.h"
#include "DBG.h"

EspTemperatureService::EspTemperatureService() {
  timer = xTimerCreate(
    "temp-service",
    pdMS_TO_TICKS(TEMPERATURE_READ_TIMER),
    pdTRUE,
    this,
    EspTemperatureService::read
  );
  xTimerStart(timer, 0);
}

float EspTemperatureService::get() {
  int adc = analogRead(NTC_PIN);

  if (adc <= 0 || adc >= ADC_MAX) {
    DBG("[TemperatureService] Invalid ADC reading");
    return 0;
  }

  // Converter ADC para resistência do NTC
  float voltageRatio = (ADC_MAX / adc) - 1.0;
  float ntcResistance = SERIES_RESISTOR / voltageRatio;

  // Fórmula Beta
  float temperature;
  temperature = ntcResistance / NOMINAL_RESISTANCE;    // (R/Ro)
  temperature = log(temperature);                      // ln(R/Ro)
  temperature /= B_COEFFICIENT;                        // 1/B * ln(R/Ro)
  temperature += 1.0 / (NOMINAL_TEMPERATURE + 273.15); // + (1/To)
  temperature = 1.0 / temperature;                     // inverso
  temperature -= 273.15;                               // Kelvin → Celsius

  for (auto o : observers) {
    o->onRead(temperature);
  }
  return temperature;
}

void EspTemperatureService::registerObserver(TemperatureObserver *observer) {
  observers.push_back(observer);
}

void EspTemperatureService::unregisterObserver(TemperatureObserver *observer) {
  observers.erase(std::remove(observers.begin(), observers.end(), observer),
                  observers.end());
}

void EspTemperatureService::read(TimerHandle_t xTimer) {
  auto *service = static_cast<EspTemperatureService *>(pvTimerGetTimerID(xTimer));
  service->get();
}
