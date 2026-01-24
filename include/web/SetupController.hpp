#pragma once

#include "network/WifiSTA.hpp"
#include "network/WifiStorage.hpp"
#include "network/dto/WifiNetworkDto.hpp"
#include <Arduino.h>
#include <WebServer.h>

class SetupController {
public:
  SetupController(WifiStorage &wifiStorage, WifiSTA &wifiSTA,
              WifiNetworkPtr statusNetwork, WifiNetworkListPtr networks)
      : wifiStorage(wifiStorage), wifiSTA(wifiSTA),
        statusNetwork(statusNetwork), networks(networks) {}
  void setup();
  void start();
  void stop();
  void loop();

private:
  bool running{false};
  WebServer server{80};

  WifiStorage &wifiStorage;
  WifiSTA &wifiSTA;
  WifiNetworkPtr statusNetwork;
  WifiNetworkListPtr networks;

  static void handleSetup(SetupController &setupServer);
  static void handleList(SetupController &setupServer);
  static void handleStatus(SetupController &setupServer);
  static void handleFile(SetupController &setupServer);
  static String getContentType(String filename);
};
