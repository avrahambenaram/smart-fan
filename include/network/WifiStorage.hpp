#pragma once

#include "network/dto/WifiConnectDto.hpp"

class WifiStorage {
public:
  virtual std::optional<WifiConnectDto> restore() = 0;
  virtual void save(WifiConnectDto dto) = 0;

  virtual ~WifiStorage() = default;
};
