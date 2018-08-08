#ifndef APPLICATION_CONFIGURATION_SERVER_H_
#define APPLICATION_CONFIGURATION_SERVER_H_

#include "configuration_storage.h"
#include "common/lamp_config.h"

class ConfigurationServer {
public:
  ConfigurationServer(ConfigurationStorage* storage);

private:
  char _uri[256];
  ConfigurationStorage* _storage;
  lamp_config_t _config;
};

#endif // APPLICATION_CONFIGURATION_SERVER_H_
