#pragma once

class FanService {
public:
  virtual ~FanService() = default;

  virtual bool isPowered();
  virtual void toggle();
  virtual void powerOn();
  virtual void powerOff();
};
