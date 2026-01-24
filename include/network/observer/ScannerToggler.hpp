#pragma once

#include "network/WifiObserver.hpp"
#include "network/WifiScanner.hpp"

class ScannerToggler : public WifiObserver {
public:
  ScannerToggler(WifiScanner &scanner);
  void onConnect() override;
  void onDisconnect() override;

private:
  WifiScanner &scanner;
};
