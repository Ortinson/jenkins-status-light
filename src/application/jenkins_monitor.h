#ifndef APPLICATION_JENKINS_MONITOR_H_
#define APPLICATION_JENKINS_MONITOR_H_

#include <ArduinoJson.h>
#include "configuration_storage.h"

class JenkinsMonitor {
public:
  JenkinsMonitor(ConfigurationStorage* configStorage);
  void Start();
  void OnConfigUpdate();

private:
  void Monitor();
  int GetBranchStatus();
  ConfigurationStorage* _config_storage;
};

#endif // APPLICATION_JENKINS_MONITOR_H_
