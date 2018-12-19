#include "configuration_storage.h"

ConfigurationStorage::ConfigurationStorage() {
  EEPROM.begin(sizeof(lamp_config_t));
  EEPROM.get(this->_eeprom_addr, this->_config);

  if(this->_config.valid_config != this->_default_config.valid_config) {
    Serial.println("Updating config to flash");
    this->_config = this->_default_config;
    this->StoreConfig(&this->_config);
  }
}

lamp_config_t* ConfigurationStorage::GetStoredConfig() {
  return &_config;
}

void ConfigurationStorage::StoreConfig(lamp_config_t* config) {
  this->_config = *config;
  EEPROM.put(this->_eeprom_addr, this->_config);
  EEPROM.commit();
  if(this->_callback) {
    this->_callback();
  }
}

void ConfigurationStorage::SetDeviceName(String conf) {
  conf.toCharArray(static_cast<char*>(this->_config.device_name), sizeof(this->_config.device_name));
  this->StoreConfig(&this->_config);
}
void ConfigurationStorage::SetMonitorPeriod(String conf) {
  this->_config.monitor_period = std::atoi(conf.c_str());
  this->StoreConfig(&this->_config);
}
void ConfigurationStorage::SetBuildPeriod(String conf) {
  this->_config.build_period = std::atoi(conf.c_str());
  this->StoreConfig(&this->_config);
}
void ConfigurationStorage::SetJenkinsPassword(String conf) {
  conf.toCharArray(static_cast<char*>(this->_config.jenkins_password), sizeof(this->_config.jenkins_password));
  this->StoreConfig(&this->_config);
}
void ConfigurationStorage::SetJenkinsUser(String conf) {
  conf.toCharArray(static_cast<char*>(this->_config.jenkins_user), sizeof(this->_config.jenkins_user));
  this->StoreConfig(&this->_config);
}
void ConfigurationStorage::SetUri(String conf) {
  conf.toCharArray(static_cast<char*>(this->_config.uri), sizeof(this->_config.uri));
  this->StoreConfig(&this->_config);
}

void ConfigurationStorage::SubscribeToConfigChange(std::function<void(void)> callback) {
  this->_callback = callback;
}

void ConfigurationStorage::SetSuccessColor(String conf) {
  Notification* n = SelectNotification(&this->_config, SUCCESS);
  n->color = ::HTMLToColor(conf);
  this->StoreConfig(&this->_config);
}

void ConfigurationStorage::SetFailureColor(String conf) {
  Notification* n = SelectNotification(&this->_config, FAILURE);
  n->color = ::HTMLToColor(conf);
  this->StoreConfig(&this->_config);
}

void ConfigurationStorage::SetRunningColor(String conf) {
  Notification* n = SelectNotification(&this->_config, RUNNING);
  n->color = ::HTMLToColor(conf);
  this->StoreConfig(&this->_config);
}

void ConfigurationStorage::SetErrorColor(String conf) {
  Notification* n = SelectNotification(&this->_config, SERVER_ERROR);
  n->color = ::HTMLToColor(conf);
  this->StoreConfig(&this->_config);
}

void ConfigurationStorage::SetSuccessAnimation(String conf) {
  Notification* n = SelectNotification(&this->_config, SUCCESS);
  n->animation = static_cast<animation_t>(atoi(conf.c_str()));
  this->StoreConfig(&this->_config);
}

void ConfigurationStorage::SetFailureAnimation(String conf) {
  Notification* n = SelectNotification(&this->_config, FAILURE);
  n->animation = static_cast<animation_t>(atoi(conf.c_str()));
  this->StoreConfig(&this->_config);
}

void ConfigurationStorage::SetRunningAnimation(String conf) {
  Notification* n = SelectNotification(&this->_config, RUNNING);
  n->animation = static_cast<animation_t>(atoi(conf.c_str()));
  this->StoreConfig(&this->_config);
}

void ConfigurationStorage::SetErrorAnimation(String conf) {
  Notification* n = SelectNotification(&this->_config, SERVER_ERROR);
  n->animation = static_cast<animation_t>(atoi(conf.c_str()));
  this->StoreConfig(&this->_config);
}

void ConfigurationStorage::SetSuccessPeriod(String conf) {
  Notification* n = SelectNotification(&this->_config, SUCCESS);
  n->period = std::atoi(conf.c_str());
  this->StoreConfig(&this->_config);
}

void ConfigurationStorage::SetFailurePeriod(String conf) {
  Notification* n = SelectNotification(&this->_config, FAILURE);
  n->period = std::atoi(conf.c_str());
  this->StoreConfig(&this->_config);
}

void ConfigurationStorage::SetRunningPeriod(String conf) {
  Notification* n = SelectNotification(&this->_config, RUNNING);
  n->period = std::atoi(conf.c_str());
  this->StoreConfig(&this->_config);
}

void ConfigurationStorage::SetErrorPeriod(String conf) {
  Notification* n = SelectNotification(&this->_config, SERVER_ERROR);
  n->period = std::atoi(conf.c_str());
  this->StoreConfig(&this->_config);
}
