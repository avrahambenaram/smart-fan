#include "network/observer/ScannerToggler.hpp"

ScannerToggler::ScannerToggler(WifiScanner &scanner) : scanner(scanner) {}

void ScannerToggler::onConnect() {
  scanner.stop();
}

void ScannerToggler::onDisconnect() {
  scanner.start();
}
