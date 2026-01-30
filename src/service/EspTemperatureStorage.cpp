#include "service/imp/EspTemperatureStorage.hpp"
#include "Config.h"

TemperatureDto EspTemperatureStorage::restore() {
  auto active = prefs.getBool("temperature", true);
  auto temp = prefs.getFloat("powering-temp", TEMPERATURE_POWERING);
  TemperatureDto settings{
    active,
    temp
  };
  return settings;
}

void EspTemperatureStorage::save(const TemperatureDto &dto) {
  prefs.putBool("temperature", dto.enabled);
  prefs.putFloat("powering-temp", dto.poweringTemperature);
}
