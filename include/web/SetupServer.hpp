#pragma once

#include "network/WifiSTA.hpp"
#include "network/WifiStorage.hpp"
#include "network/dto/WifiNetworkDto.hpp"
#include <Arduino.h>
#include <WebServer.h>

class SetupServer {
public:
  SetupServer(WifiStorage &wifiStorage, WifiSTA &wifiSTA,
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

  static void handleSetup(SetupServer &setupServer);
  static void handleList(SetupServer &setupServer);
  static void handleStatus(SetupServer &setupServer);
  static void handleFile(SetupServer &setupServer);
  static String getContentType(String filename);
};
