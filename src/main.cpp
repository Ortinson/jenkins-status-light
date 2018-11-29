#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>        //https://github.com/arkhipenko/TaskScheduler

// Needed for wifi manager library
// #include <DNSServer.h>
// #include <ESP8266WebServer.h>
// #include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include "application/configuration_storage.h"
#include "application/configuration_server.h"
#include "application/jenkins_monitor.h"
#include "application/LED_notifier.h"

ConfigurationStorage* storage;
ConfigurationServer* server;
JenkinsMonitor* monitor;
LEDNotifier* notifier;

Scheduler scheduler; 

void setup() {
    Serial.begin(9600);
    Serial.println("starting setup");
    storage = new ConfigurationStorage();
    server = new ConfigurationServer(storage);
    notifier = new LEDNotifier();
    monitor = new JenkinsMonitor(storage, notifier, &scheduler);

    const char* ssid = "ssid";
    const char* password = "password";
    // TODO(Ortinson): find a way to manage wifi connection that is compatible
    //   with 'ESP async web server'    // WiFiManager wifiManager;
    // wifiManager.autoConnect(storage->GetStoredConfig().device_name);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.printf("Connecting to WiFi. Status: %d\n", WiFi.status());
    }

    Serial.printf("connected. IP: %s\n", WiFi.localIP().toString().c_str());

    server->Start();
}

void loop() {
  notifier->Cycle();
  scheduler.execute();
}
