#pragma once

#include "network/WifiSTA.hpp"
#include "network/WifiStorage.hpp"
#include "network/dto/WifiNetworkDto.hpp"
#include <Arduino.h>
#include <WebServer.h>

class SetupController {
public:
  SetupController(WebServer &server, WifiStorage &wifiStorage, WifiSTA &wifiSTA,
              WifiNetworkPtr statusNetwork, WifiNetworkListPtr networks)
      : server(server), wifiStorage(wifiStorage), wifiSTA(wifiSTA),
        statusNetwork(statusNetwork), networks(networks) {}
  void setup();

private:
  bool running{false};
  WebServer &server;

  WifiStorage &wifiStorage;
  WifiSTA &wifiSTA;
  WifiNetworkPtr statusNetwork;
  WifiNetworkListPtr networks;

  static void handleSetup(SetupController &setupServer);
  static void handleList(SetupController &setupServer);
  static void handleStatus(SetupController &setupServer);
};
