#pragma once

class TemperatureService {
public:
  virtual ~TemperatureService() = default;

  virtual bool isEnabled() = 0;
  virtual void enable() = 0;
  virtual void disable() = 0;
  virtual void toggle() = 0;
  virtual void setPoweringTemperature(float temp) = 0;
  virtual float getPoweringTemperature() = 0;
};
