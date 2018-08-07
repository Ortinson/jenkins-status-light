#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "config.h"

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    // Setup led driver and set it to notify connection mode

    WiFiManager wifiManager;
    wifiManager.autoConnect(device_name);
    Serial.println("connected...yeey :)");

    // Start setup server
    // Start jenkins monitor
}

void loop() {
    // put your main code here, to run repeatedly:

}
