#ifndef APPLICATION_JENKINS_MONITOR_H_
#define APPLICATION_JENKINS_MONITOR_H_

#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
// #include "Ticker.h"
#include "configuration_storage.h"
#include "LED_notifier.h"
#include "common/lamp_config.h"

// URI example: http://jenkins.me-client.com/job/DBI-Firmware/job/dbi-icbis-controller/job/master/lastBuild/api/json?pretty=false
// https://restninja.io/
class JenkinsMonitor {
public:
  JenkinsMonitor(ConfigurationStorage* configStorage, LEDNotifier* notifier, uint period);
  void Monitor();
  void Start();
  void Stop();

private:
  void OnConfigUpdate();
  jenkins_status_t GetJenkinsStatus();
  jenkins_status_t ParseResponse(const String response);
  ConfigurationStorage* _config_storage;
  LEDNotifier* _notifier;
  WiFiClient _client;
  HTTPClient _http;
  uint _period;
  // Ticker _myTicker;
};

#endif // APPLICATION_JENKINS_MONITOR_H_
