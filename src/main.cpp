#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

// Needed for wifi manager library
// #include <DNSServer.h>
// #include <ESP8266WebServer.h>
// #include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include "application/configuration_storage.h"
#include "application/configuration_server.h"

ConfigurationStorage* storage;
ConfigurationServer* server;
void setup() {
    Serial.begin(115200);
    Serial.println("starting setup");
    storage = new ConfigurationStorage();
    server = new ConfigurationServer(storage);
    // TODO(Ortinson): Initialize LEDDriver
    // TODO(Ortinson): Initialize JenkinsMonitor
    // TODO(Ortinson): Setup led driver and set it to notify connection mode


    // TODO(Ortinson): find a way to manage wifi connection that is compatible
    //   with 'ESP async web server'    // WiFiManager wifiManager;
    // wifiManager.autoConnect(storage->GetStoredConfig().device_name);
    // Serial.println("connected...yeey :)");

    // Start jenkins monitor
}

void loop() {

  while(true){
    Serial.println("caca");
    delay(1000);
  }
    // put your main code here, to run repeatedly:

}
