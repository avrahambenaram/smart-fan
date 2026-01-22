#include "network/WifiSTA.hpp"
#include "DBG.h"

void WifiSTA::reconnect() { WiFi.reconnect(); }

bool WifiSTA::isConnected() {
  return WiFi.status() == WL_CONNECTED && WiFi.localIP() != INADDR_NONE;
}

void WifiSTA::connect(WifiConnectDto connectCmd) {
  if (connectCmd.isDHCP())
    connectDHCP(connectCmd);
  else
    connectStatic(connectCmd);
}

void WifiSTA::connectDHCP(WifiConnectDto connectCmd) {
  DBGF("Connecting to WiFi [DHCP]: %s\n", connectCmd.ssid);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
  connect(connectCmd.ssid, connectCmd.pass);
}

void WifiSTA::connectStatic(WifiConnectDto connectCmd) {
  DBG("Connecting to WiFi [Static]:");
  DBG(connectCmd.ssid);
  DBG("IP: " + connectCmd.ip);
  DBG("Gateway: " + connectCmd.gateway);
  DBG("Subnet: " + connectCmd.subnet);

  IPAddress ipParsed, gatewayParsed, subnetParsed;
  IPAddress dns1(8, 8, 8, 8);
  IPAddress dns2(8, 8, 4, 4);

  auto failParseIps = !ipParsed.fromString(connectCmd.ip) ||
                      !gatewayParsed.fromString(connectCmd.gateway) ||
                      !subnetParsed.fromString(connectCmd.subnet);
  if (failParseIps)
    return;

  WiFi.config(ipParsed, gatewayParsed, subnetParsed, dns1, dns2);
  connect(connectCmd.ssid, connectCmd.pass);
}

void WifiSTA::connect(String ssid, String pass) {
  if (isConnected())
    WiFi.disconnect();

  WiFi.setAutoReconnect(false);
  WiFi.begin(ssid.c_str(), pass.c_str());
  int tries = 0;
  while (!isConnected() && tries < 25) {
    vTaskDelay(pdMS_TO_TICKS(200));
    tries++;
  }
  if (isConnected()) {
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}
