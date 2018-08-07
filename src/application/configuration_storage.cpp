#include "configuration_storage.h"

ConfigurationStorage::ConfigurationStorage() {
  Serial.println("Getting EEPROM config");
  EEPROM.begin(sizeof(struct LampConfig));
  EEPROM.get(this->_eeprom_addr, this->_config);

  if(this->_config.valid_config != this->_default_config.valid_config) {
    this->StoreConfig(const_cast<LampConfig*>(&this->_default_config));
  }
}

LampConfig ConfigurationStorage::GetStoredConfig() {
  return _config;
}

void ConfigurationStorage::StoreConfig(LampConfig* config) {
  this->_config = *config;
  EEPROM.put(this->_eeprom_addr, this->_config);
  EEPROM.commit();
}
