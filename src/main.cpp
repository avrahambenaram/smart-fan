#include <Arduino.h>
#include <math.h>

#include "Config.h"
#include "DBG.h"

void setup() {
  Serial.begin(9600);

  // ADC Configuration
  analogReadResolution(ESP32_ADC_BITS);
  analogSetAttenuation(ADC_11db);

  pinMode(NTC_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  delay(1000);
}

void loop() {
  int adc = analogRead(NTC_PIN);

  if (adc <= 0 || adc >= ADC_MAX) {
    Serial.println("Invalid ADC reading");
    delay(2000);
    return;
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

  DBGF("ADC: %d --- Temperature: %.2f\n", adc, temperature);

  delay(1000);
}
