#include "network/observer/WebToggler.hpp"

WebToggler::WebToggler(SetupServer &setupServer) : setupServer(setupServer) {}

void WebToggler::onConnect() {
  setupServer.stop();
}

void WebToggler::onDisconnect() {
  setupServer.start();
}
