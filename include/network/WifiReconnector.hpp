#pragma once

class WifiReconnector {
public:
  virtual ~WifiReconnector() = default;

  virtual void start();
  virtual void stop();
};
