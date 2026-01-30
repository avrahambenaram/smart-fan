#pragma once

class TemperatureService {
public:
  virtual ~TemperatureService() = default;

  virtual void enable() = 0;
  virtual void disable() = 0;
  virtual void toggle() = 0;
  virtual void setPoweringTemperature(float temp) = 0;
};
