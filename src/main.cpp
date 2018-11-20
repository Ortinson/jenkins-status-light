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
    notifier = new LEDNotifier(1,1);
    monitor = new JenkinsMonitor(storage, notifier);

    const char* ssid = "ORPA_CH6_3";
    const char* password = "Alcornoque22";
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
  size_t i = 0;
  monitor->Monitor();

  while(true){
    Serial.printf("%d\n",++i);
    delay(1000);
  }
}
