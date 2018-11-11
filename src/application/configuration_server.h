#ifndef APPLICATION_CONFIGURATION_SERVER_H_
#define APPLICATION_CONFIGURATION_SERVER_H_

#include <ESPAsyncWebServer.h>
#include <SPIFFSEditor.h>

#include "configuration_storage.h"
#include "common/lamp_config.h"

class ConfigurationServer {
public:
  ConfigurationServer(ConfigurationStorage* storage);

private:
  ConfigurationStorage* _storage;
  lamp_config_t _config;
  AsyncWebServer* _server;

  void setURIS();
  void start();
};

#endif // APPLICATION_CONFIGURATION_SERVER_H_
