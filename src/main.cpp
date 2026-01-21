
#include <Arduino.h>
#include <math.h>

#define NTC_PIN 33
#define RELAY_PIN 2

// Parâmetros do NTC (ajuste se o seu for diferente)
#define SERIES_RESISTOR 9500.0    // resistor fixo (10k)
#define NOMINAL_RESISTANCE 8500.0 // NTC a 25°C
#define NOMINAL_TEMPERATURE 22.0  // °C
#define B_COEFFICIENT 3950.0

void setup() {
  Serial.begin(9600);

  // Configuração do ADC
  analogReadResolution(12);       // 0–4095
  analogSetAttenuation(ADC_11db); // até ~3.3V

  pinMode(NTC_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  delay(1000);
}

void loop() {
  int adc = analogRead(NTC_PIN);

  // Evita divisão por zero
  if (adc <= 0 || adc >= 4095) {
    Serial.println("Leitura ADC inválida");
    delay(2000);
    return;
  }

  // Converter ADC para resistência do NTC
  float voltageRatio = (4095.0 / adc) - 1.0;
  float ntcResistance = SERIES_RESISTOR / voltageRatio;

  // Fórmula Beta
  float temperature;
  temperature = ntcResistance / NOMINAL_RESISTANCE;    // (R/Ro)
  temperature = log(temperature);                      // ln(R/Ro)
  temperature /= B_COEFFICIENT;                        // 1/B * ln(R/Ro)
  temperature += 1.0 / (NOMINAL_TEMPERATURE + 273.15); // + (1/To)
  temperature = 1.0 / temperature;                     // inverso
  temperature -= 273.15;                               // Kelvin → Celsius

  Serial.print("ADC: ");
  Serial.print(adc);
  Serial.print(" | Temp: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000);
}
