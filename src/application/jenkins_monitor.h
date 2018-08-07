#ifndef APPLICATION_JENKINS_MONITOR_H_
#define APPLICATION_JENKINS_MONITOR_H_

#include <ArduinoJson.h>
#include "configuration_storage.h"
#include "drivers/LED_driver.h"

class JenkinsMonitor {
public:
  JenkinsMonitor(ConfigurationStorage* configStorage);

private:
  ConfigurationStorage* _config_storage;
};

#endif // APPLICATION_JENKINS_MONITOR_H_
