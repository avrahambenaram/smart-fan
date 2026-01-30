#pragma once

#include "service/TemperatureStorage.hpp"
#include "Preferences.h"

class EspTemperatureStorage : public TemperatureStorage {
public:
  EspTemperatureStorage(Preferences &prefs) : prefs(prefs) {}

  TemperatureDto restore() override;
  void save(const TemperatureDto &dto) override;

private:
  Preferences &prefs;
};
