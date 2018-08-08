#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include "configuration_server.h"

ConfigurationServer::ConfigurationServer(ConfigurationStorage* storage)
  : _storage(storage) {
    this->_config = this->_storage->GetStoredConfig();
    StartServer();
  }

  void ConfigurationServer::handleClient() {
    this->_server->handleClient();
  }

  void ConfigurationServer::StartServer() {
    this->_server = new ESP8266WebServer(80);
    this->_server->on(String(F("/")), std::bind(&ConfigurationServer::handleRoot, this));
    this->_server->begin();
  }

  void ConfigurationServer::handleRoot() {
    const char* _customHeadElement = "";
    const char* _apName = "no-net";
    String page = FPSTR(_HTTP_HEAD);
    page.replace("{v}", "Options");
    page += FPSTR(_HTTP_SCRIPT);
    page += FPSTR(_HTTP_STYLE);
    page += _customHeadElement;
    page += FPSTR(_HTTP_HEAD_END);
    page += String(F("<h1>"));
    page += _apName;
    page += String(F("</h1>"));
    page += String(F("<h3>WiFiManager</h3>"));
    page += FPSTR(_HTTP_PORTAL_OPTIONS);
    page += FPSTR(_HTTP_END);

    this->_server->sendHeader("Content-Length", String(page.length()));
    this->_server->send(200, "text/html", page);

  }

//Initiate server
// store new config when requested by website
  // find example where each page can be one file
  // add one example of changing one parameter from root page
