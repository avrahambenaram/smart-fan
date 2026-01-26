#pragma once

#include "service/FanService.hpp"
#include <vector>

class EspFanService : public FanService {
public:
  bool isPowered() override;
  void toggle() override;
  void powerOn() override;
  void powerOff() override;
  void registerObserver(FanObserver *observer) override;
  void unregisterObserver(FanObserver *observer) override;

private:
  bool powered{false};
  std::vector<FanObserver *> observers;
};
