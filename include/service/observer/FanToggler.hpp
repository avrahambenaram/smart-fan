#pragma once

#include "service/FanObserver.hpp"

class FanToggler : public FanObserver {
public:
  FanToggler();
  void onPowerOn() override;
  void onPowerOff() override;
};
