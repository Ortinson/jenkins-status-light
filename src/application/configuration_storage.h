#ifndef APPLICATION_CONFIGURATION_STORAGE_H_
#define APPLICATION_CONFIGURATION_STORAGE_H_

#include "common/lamp_config.h"
#include <EEPROM.h>

class ConfigurationStorage {
public:
  ConfigurationStorage(void);
  LampConfig GetStoredConfig(void);
  void StoreConfig(LampConfig* config);

private:
  static const int _eeprom_addr = 0;
  // TODO set to progmem
  const LampConfig _default_config = {
    .build_ok = {{{0, 254, 0}}, animation_t::Pulse, 5},
    .build_err = {{{254, 0, 0}}, animation_t::Pulse, 1},
    .build_running = {{{254, 254, 0}}, animation_t::Pulse, 5},
    .server_down = {{{254, 0, 254}}, animation_t::Pulse, 1},
    .internet_down = {{{0, 0, 254}}, animation_t::Pulse, 5},
    .wifi_down = {{{0, 0, 254}}, animation_t::Pulse, 5},
    .monitor_period = 60,
    .build_period = 10,
    .jenkins_password = "",
    .uri = "",
    .device_name = "Jenkins Status Light",
    .valid_config = 0xDEADBEEE
  };
  LampConfig _config;

};

#endif // APPLICATION_CONFIGURATION_STORAGE_H_
