#pragma once

#include "TemperatureObserver.hpp"

class TemperatureService {
public:
  virtual ~TemperatureService() = default;

  virtual float get();
  virtual void registerObserver(TemperatureObserver *observer);
  virtual void unregisterObserver(TemperatureObserver *observer);
};
