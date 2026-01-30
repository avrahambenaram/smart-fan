#include <Arduino.h>

#include "hardware/EspTemperatureReader.hpp"
#include "Config.h"
#include "DBG.h"

float EspTemperatureReader::read() {
  int adc = analogRead(NTC_PIN);

  if (adc <= 0 || adc >= ADC_MAX) {
    DBG("[TemperatureReader] Invalid ADC reading");
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

  DBGF("[TemperatureReader] Current temperature: %.2f\n", temperature);
  return temperature;
}
