#ifndef APPLICATION_JENKINS_MONITOR_H_
#define APPLICATION_JENKINS_MONITOR_H_

#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#define _TASK_STD_FUNCTION
#include <TaskSchedulerDeclarations.h>

#include "configuration_storage.h"
#include "LED_notifier.h"
#include "common/lamp_config.h"

class JenkinsMonitor {
public:
  JenkinsMonitor(ConfigurationStorage* configStorage, LEDNotifier* notifier, Scheduler* scheduler);
  void Monitor();

private:
  void OnConfigUpdate();
  jenkins_status_t GetJenkinsStatus();
  jenkins_status_t ParseResponse(const String response);
  lamp_config_t* _config;
  ConfigurationStorage* _config_storage;
  LEDNotifier* _notifier;
  
  WiFiClient _client;
  HTTPClient _http;
  Scheduler* _scheduler;
  Task* _t1;
  uint _period;
};

#endif // APPLICATION_JENKINS_MONITOR_H_
