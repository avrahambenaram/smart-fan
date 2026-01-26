#pragma once

#include "service/FanObserver.hpp"

class FanService {
public:
  virtual ~FanService() = default;

  virtual bool isPowered();
  virtual void toggle();
  virtual void powerOn();
  virtual void powerOff();
  virtual void registerObserver(FanObserver *observer);
  virtual void unregisterObserver(FanObserver *observer);
};
