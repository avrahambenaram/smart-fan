#pragma once

#include "service/FanService.hpp"

class EspFanService : public FanService {
public:
  EspFanService();
  bool isPowered() override;
  void toggle() override;
  void powerOn() override;
  void powerOff() override;

private:
  bool powered{false};

};
