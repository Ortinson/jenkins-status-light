#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>        //https://github.com/arkhipenko/TaskScheduler

// TODO(Ortinson): Implement night time (NTP + configurable time from web interface)
#include "application/configuration_storage.h"
#include "application/configuration_server.h"
#include "application/jenkins_monitor.h"
#include "application/LED_notifier.h"

bool need_to_restart = false;

ConfigurationStorage* storage;
ConfigurationServer* server;
JenkinsMonitor* monitor;
LEDNotifier* notifier;
WiFiManager* wifiManager;

Scheduler scheduler;

void configModeCallback (WiFiManager *myWiFiManager) {
  need_to_restart = true;
}

void ConnectToWiFi(ConfigurationStorage* storage) {
    wifiManager = new WiFiManager();
    wifiManager->setAPCallback(configModeCallback);
    wifiManager->autoConnect(storage->GetStoredConfig()->device_name);
    if (need_to_restart)
      ESP.restart();
    Serial.printf("connected. IP: %s\n", WiFi.localIP().toString().c_str());
}

void setup() {
    Serial.begin(9600);
    storage = new ConfigurationStorage();
    notifier = new LEDNotifier();
    monitor = new JenkinsMonitor(storage, notifier, &scheduler);

    ConnectToWiFi(storage);

    server = new ConfigurationServer(storage);
    server->Start();
}

void loop() {
  notifier->Cycle();
  scheduler.execute();
}
