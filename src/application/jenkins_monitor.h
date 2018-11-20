#ifndef APPLICATION_JENKINS_MONITOR_H_
#define APPLICATION_JENKINS_MONITOR_H_

#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include "configuration_storage.h"
#include "LED_notifier.h"
#include "common/lamp_config.h"

// URI example: http://jenkins.me-client.com/job/DBI-Firmware/job/dbi-icbis-controller/job/master/lastBuild/api/json?pretty=false
// https://restninja.io/
class JenkinsMonitor {
public:
  JenkinsMonitor(ConfigurationStorage* configStorage, LEDNotifier* notifier);
  void Monitor();

private:
  void OnConfigUpdate();
  jenkins_status_t GetBranchStatus();
  jenkins_status_t ParseResponse(const String response);
  ConfigurationStorage* _config_storage;
  LEDNotifier* _notifier;
  WiFiClient _client;
  HTTPClient _http;
};

#endif // APPLICATION_JENKINS_MONITOR_H_
