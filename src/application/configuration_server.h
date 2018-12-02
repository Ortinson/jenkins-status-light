#ifndef APPLICATION_CONFIGURATION_SERVER_H_
#define APPLICATION_CONFIGURATION_SERVER_H_

#include <ESPAsyncWebServer.h>  // https://github.com/me-no-dev/ESPAsyncWebServer
#include <SPIFFSEditor.h>

#include "configuration_storage.h"
#include "common/lamp_config.h"
#include "common/utils.h"

class ConfigurationServer {
public:
  ConfigurationServer(ConfigurationStorage* storage);
  void Start();

private:
  ConfigurationStorage* _storage;
  lamp_config_t* _config;
  AsyncWebServer* _server;
  
  void SendIndex(AsyncWebServerRequest *request);
  void UpdateConfig(AsyncWebServerRequest *request);
  String MakeSelectList(jenkins_status_t status);
  String IndexTemplateProcessor(const String& var);
  void setURIS();
};

#endif // APPLICATION_CONFIGURATION_SERVER_H_
