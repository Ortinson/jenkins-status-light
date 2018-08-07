#ifndef APPLICATION_CONFIGURATION_STORAGE_H_
#define APPLICATION_CONFIGURATION_STORAGE_H_

#include "common/lamp_config.h"

class ConfigurationStorage {
public:
  ConfigurationStorage(void);
  LampConfig GetStoredConfig(void);
  void StoreConfig(LampConfig config);

private:
  LampConfig* _flash_config;
};

#endif // APPLICATION_CONFIGURATION_STORAGE_H_
