#include "network/imp/EspWifiStorage.hpp"
#include "DBG.h"

std::optional<WifiConnectDto> EspWifiStorage::restore() {
  auto ssid = prefs.getString("wifi-ssid");
  if (ssid == "")
    return std::nullopt;
  auto pass = prefs.getString("wifi-pass");
  auto ip = prefs.getString("wifi-ip");
  auto gateway = prefs.getString("wifi-gateway");
  auto subnet = prefs.getString("wifi-subnet");
  WifiConnectDto dto{ssid, pass, ip, gateway, subnet};
  DBG("[Wifi storage] restored");
  return dto;
}

void EspWifiStorage::save(WifiConnectDto dto) {
  DBG("[Wifi storage] saving...");
  prefs.putString("wifi-ssid", dto.ssid);
  prefs.putString("wifi-pass", dto.pass);
  prefs.putString("wifi-ip", dto.ip);
  prefs.putString("wifi-gateway", dto.gateway);
  prefs.putString("wifi-subnet", dto.subnet);
}
