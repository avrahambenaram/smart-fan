#include "network/observer/Reconnector.hpp"

void Reconnector::onConnect() { wifiReconnector.start(); }

void Reconnector::onDisconnect() { wifiReconnector.stop(); }
