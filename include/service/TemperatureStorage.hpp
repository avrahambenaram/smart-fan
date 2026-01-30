#pragma once

#include "service/dto/TemperatureDto.hpp"

class TemperatureStorage {
public:
  virtual ~TemperatureStorage() = default;

  virtual TemperatureDto restore() = 0;
  virtual void save(const TemperatureDto &dto) = 0;
};
