#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
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

void setup() {
    Serial.begin(9600);
    Serial.println("starting setup");
    storage = new ConfigurationStorage();
    server = new ConfigurationServer(storage);
    notifier = new LEDNotifier();
    monitor = new JenkinsMonitor(storage, notifier, 10); //TODO(Ortinson): fetch period from configuration server

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
  monitor->Monitor();
  unsigned long monitor_period = storage->GetStoredConfig().monitor_period * 1000;
  unsigned long next_trigger = millis() + monitor_period;
  unsigned long t;
  while(true){
    notifier->Cycle();
    t = millis();
    if (t > next_trigger){
      Serial.println("going to monitor");
      next_trigger = t + monitor_period;
      monitor->Monitor();
    }
    delay(10);  // TODO(Ortinson): Investigate why watchdog barks if no delay()  
  }
}
