#include <Arduino.h>
#include <Preferences.h>
#include <math.h>
#include <memory>

#include "Config.h"
#include "DBG.h"
#include "network/WifiManager.hpp"
#include "network/dto/WifiNetworkDto.hpp"
#include "network/imp/EspWifiAP.hpp"
#include "network/imp/EspWifiSTA.hpp"
#include "network/imp/EspWifiScanner.hpp"
#include "network/imp/EspWifiStorage.hpp"
#include "network/observer/APToggler.hpp"
#include "network/observer/MDNSToggler.hpp"
#include "network/observer/Reconnector.hpp"
#include "network/observer/ToggleIndicator.hpp"
#include "web/SetupServer.hpp"

auto statusNetwork = std::make_shared<WifiNetworkDto>();
auto networks = std::make_shared<WifiNetworkList>();
Preferences prefs;
EspWifiAP wifiAP;
EspWifiScanner wifiScanner{networks, statusNetwork};
EspWifiStorage wifiStorage{prefs};
EspWifiSTA wifiSTA{statusNetwork};
WifiManager wifi{wifiAP, wifiScanner, wifiStorage, wifiSTA};
SetupServer setupServer{wifiStorage, wifiSTA, statusNetwork, networks};

void setup() {
  Serial.begin(9600);

  // ADC Configuration
  analogReadResolution(ESP32_ADC_BITS);
  analogSetAttenuation(ADC_11db);

  pinMode(NTC_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  delay(1000);

  prefs.begin("smartfan", false);
  wifiSTA.registerObserver(new APToggler(wifiAP));
  wifiSTA.registerObserver(new Reconnector(wifiStorage, wifiSTA));
  wifiSTA.registerObserver(new ToggleIndicator());
  wifiSTA.registerObserver(new MDNSToggler());

  wifi.setup();
  wifi.start();

  setupServer.setup();
  setupServer.start();
}

void loop() {
  // int adc = analogRead(NTC_PIN);
  //
  // if (adc <= 0 || adc >= ADC_MAX) {
  //   Serial.println("Invalid ADC reading");
  //   delay(2000);
  //   return;
  // }
  //
  // // Converter ADC para resistência do NTC
  // float voltageRatio = (ADC_MAX / adc) - 1.0;
  // float ntcResistance = SERIES_RESISTOR / voltageRatio;
  //
  // // Fórmula Beta
  // float temperature;
  // temperature = ntcResistance / NOMINAL_RESISTANCE;    // (R/Ro)
  // temperature = log(temperature);                      // ln(R/Ro)
  // temperature /= B_COEFFICIENT;                        // 1/B * ln(R/Ro)
  // temperature += 1.0 / (NOMINAL_TEMPERATURE + 273.15); // + (1/To)
  // temperature = 1.0 / temperature;                     // inverso
  // temperature -= 273.15;                               // Kelvin → Celsius
  //
  // auto voltage = (adc / ADC_MAX) * NTC_V;
  //
  // DBGF("ADC: %d --- Voltage: %.4f --- Temperature: %.2fºC\n", adc, voltage,
  //      temperature);

  setupServer.loop();
  wifiAP.loop();
}
