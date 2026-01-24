#pragma once

#include "WifiAP.hpp"
#include "WifiSTA.hpp"
#include "WifiScanner.hpp"
#include "WifiStorage.hpp"
#include <queue>

class WifiManager {
public:
  WifiManager(WifiAP &ap, WifiScanner &scanner, WifiStorage &storage,
              WifiSTA &sta)
      : ap(ap), scanner(scanner), storage(storage), sta(sta) {}
  void setup();
  void start();
  void stop();

private:
  WifiAP &ap;
  WifiScanner &scanner;
  WifiStorage &storage;
  WifiSTA &sta;
};
