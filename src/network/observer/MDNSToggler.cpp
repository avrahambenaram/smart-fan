#include "network/observer/MDNSToggler.hpp"
#include <ESPmDNS.h>

void MDNSToggler::onConnect() {
  if (!MDNS.begin("smartfan"))
    Serial.println("mDNS failed to start");
  else
    MDNS.addService("http", "tcp", 80);
}

void MDNSToggler::onDisconnect() { MDNS.end(); }
