#ifndef APPLICATION_CONFIGURATION_SERVER_H_
#define APPLICATION_CONFIGURATION_SERVER_H_

#include <String.h>
#include "configuration_storage.h"

class ConfigurationServer {
public:
  ConfigurationServer(ConfigurationStorage* storage);

private:
  char _uri[256];
  ConfigurationStorage* _storage;
  LampConfig _config;
};

#endif // APPLICATION_CONFIGURATION_SERVER_H_
