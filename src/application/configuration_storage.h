#ifndef APPLICATION_CONFIGURATION_STORAGE_H_
#define APPLICATION_CONFIGURATION_STORAGE_H_

#include "common/lamp_config.h"
#include <string>
#include <EEPROM.h>
class ConfigurationStorage {
public:
  ConfigurationStorage(void);
  lamp_config_t* GetStoredConfig(void);
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
    .notification_list = {{SUCCESS, {(uint8_t)0, (uint8_t)255, (uint8_t)0}, animation_t::ON, (uint32_t)10},
    {FAILURE,{(uint8_t)255, (uint8_t)0, (uint8_t)0}, animation_t::Pulse, (uint32_t)3},
    {RUNNING,{(uint8_t)255, (uint8_t)255, (uint8_t)0}, animation_t::Pulse, (uint32_t)5},
    {SERVER_ERROR,{(uint8_t)255, (uint8_t)0, (uint8_t)255}, animation_t::Pulse, (uint32_t)1}},
    .monitor_period = (uint32_t)60,
    .build_period = (uint32_t)10,
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
