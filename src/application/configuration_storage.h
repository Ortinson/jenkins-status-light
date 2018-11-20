#ifndef APPLICATION_CONFIGURATION_STORAGE_H_
#define APPLICATION_CONFIGURATION_STORAGE_H_

#include "common/lamp_config.h"
#include <string>
#include <EEPROM.h>
class ConfigurationStorage {
public:
  ConfigurationStorage(void);
  lamp_config_t GetStoredConfig(void);
  void StoreConfig(lamp_config_t* config);
  void SubscribeToConfigChange(std::function<void(void)> callback);
  void SetMonitorPeriod(String conf);
  void SetBuildPeriod(String conf);
  void SetJenkinsUser(String conf);
  void SetJenkinsPassword(String conf);
  void SetUri(String conf);
  void SetDeviceName(String conf);
private:
  static const int _eeprom_addr = 0;
  // TODO(Ortinson): Move to confifg file (SPIFFS).
  const lamp_config_t _default_config = {
    .build_ok = {{{0, 254, 0}}, animation_t::Pulse, 5},
    .build_err = {{{254, 0, 0}}, animation_t::Pulse, 1},
    .build_running = {{{254, 254, 0}}, animation_t::Pulse, 5},
    .build_not_found = {{{254, 254, 0}}, animation_t::Pulse, 5},
    .server_down = {{{254, 0, 254}}, animation_t::Pulse, 1},
    .internet_down = {{{0, 0, 254}}, animation_t::Pulse, 5},
    .wifi_down = {{{0, 0, 254}}, animation_t::Pulse, 5},
    .monitor_period = 60,
    .build_period = 10,
    .jenkins_user = "",
    .jenkins_password = "",
    .uri = "",
    .device_name = "Jenkins Status Light",
    .valid_config = 0xDEADBEEF
  };
  lamp_config_t _config;
  std::function<void(void)> _callback = NULL;

};

#endif // APPLICATION_CONFIGURATION_STORAGE_H_
