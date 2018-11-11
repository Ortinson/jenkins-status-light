#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include "configuration_server.h"

ConfigurationServer::ConfigurationServer(ConfigurationStorage* storage)
  : _storage(storage) {
    this->_config = this->_storage->GetStoredConfig();
    this->_server = new AsyncWebServer(80);
    this->setURIS();
  }

void ConfigurationServer::setURIS() {
  // Route for root / web page
  this->_server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String());
  });
}

void ConfigurationServer::start(){
  this->_server->begin();
}