#include "network/WifiAP.hpp"
#include <esp_wifi.h>

void WifiAP::start() {
  if (running)
    return;
  WiFi.softAPConfig(apIP, gateway, subnet);
  WiFi.softAP("Smart Fan", "smartfan1234", 1);
  dns.start(DNS_PORT, "*", apIP);

  running = true;
}

void WifiAP::stop() {
  if (!running)
    return;
  WiFi.softAPdisconnect(true);
  dns.stop();
  running = false;
}

void WifiAP::loop() {
  if (!running)
    return;

  dns.processNextRequest();
}

uint16_t WifiAP::countConnected() {
  wifi_sta_list_t sta_list;
  esp_wifi_ap_get_sta_list(&sta_list);
  return sta_list.num;
}
