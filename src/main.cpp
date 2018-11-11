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


    const char* ssid = "SSID";
    const char* password = "PASS";
    // TODO(Ortinson): find a way to manage wifi connection that is compatible
    //   with 'ESP async web server'    // WiFiManager wifiManager;
    // wifiManager.autoConnect(storage->GetStoredConfig().device_name);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi..");
    }

    Serial.println("connected...yeey :)");
    // Start jenkins monitor
}

void loop() {
  size_t i = 0;
  while(true){
    Serial.printf("%d\n",++i);
    delay(1000);
  }
    // put your main code here, to run repeatedly:

}
