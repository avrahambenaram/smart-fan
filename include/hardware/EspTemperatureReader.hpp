#pragma once

#include "service/TemperatureReader.hpp"

class EspTemperatureReader : public TemperatureReader {
public:
  float read() override;
};
