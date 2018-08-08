#include "configuration_server.h"

ConfigurationServer::ConfigurationServer(ConfigurationStorage* storage)
  : _storage(storage) {
    this->_config = this->_storage->GetStoredConfig();
  }

//Initiate server
// store new config when requested by website
