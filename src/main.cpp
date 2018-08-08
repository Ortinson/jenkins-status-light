#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "application/configuration_storage.h"
#include "application/configuration_server.h"

void setup() {
    Serial.begin(115200);
    delay(3000);
    Serial.println("starting setup");
    ConfigurationStorage* storage = new ConfigurationStorage();
    ConfigurationServer* server = new ConfigurationServer(storage);
    // Initialize ConfigurationServer
    // Initialize LEDDriver
    // Initialize JenkinsMonitor
    // Setup led driver and set it to notify connection mode

    WiFiManager wifiManager;
    wifiManager.autoConnect(storage->GetStoredConfig().device_name);
    Serial.println("connected...yeey :)");

    // Start jenkins monitor
}

void loop() {

  while(true){
    Serial.println("caca");
    delay(1000);
  }
    // put your main code here, to run repeatedly:

}
