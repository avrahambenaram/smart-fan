#pragma once

class FanObserver {
public:
  virtual ~FanObserver() = default;

  virtual void onPowerOn() = 0;
  virtual void onPowerOff() = 0;
};
