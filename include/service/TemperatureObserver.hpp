#pragma once

class TemperatureObserver {
public:
  virtual ~TemperatureObserver() = default;

  virtual void onRead(float temperature);
};
