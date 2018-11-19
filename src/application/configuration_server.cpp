#include <ESP8266WiFi.h>          // https://github.com/esp8266/Arduino
#include "configuration_server.h"

ConfigurationServer::ConfigurationServer(ConfigurationStorage* storage)
  : _storage(storage) {
    this->_config = this->_storage->GetStoredConfig();
    this->_server = new AsyncWebServer(80);
    SPIFFS.begin();
    this->setURIS();
  }

void ConfigurationServer::setURIS() {
  this->_server->serveStatic("/style.css", SPIFFS, "/style.css").setDefaultFile("index.html");  // This works
  this->_server->on("/", HTTP_GET, std::bind(&ConfigurationServer::SendIndex, this, std::placeholders::_1));
  // this->_server->on("/", HTTP_PUT, std::bind(&ConfigurationServer::UpdateConfig, this, std::placeholders::_1));

  this->_server->on("/", HTTP_POST, std::bind(&ConfigurationServer::UpdateConfig, this, std::placeholders::_1));
  // this->_server->on("/update", HTTP_GET, [](AsyncWebServerRequest *request){
  //   request->send(200, "text/html", "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>");
  // });
}

void ConfigurationServer::SendIndex(AsyncWebServerRequest *request){
  request->send(SPIFFS, "/index.html", String(), false, std::bind(&ConfigurationServer::IndexTemplateProcessor, this, std::placeholders::_1));
}

void ConfigurationServer::UpdateConfig(AsyncWebServerRequest *request){
  int args = request->args();
  for(int i=0;i<args;i++){
    Serial.printf("ARG[%s]: %s\n", request->argName(i).c_str(), request->arg(i).c_str());
  }

  String param;
  if (request->hasParam("dev_name", true)) {
    Serial.printf("dev_name\n");
    param = request->getParam("dev_name", true)->value();
    this->_storage->SetDeviceName(param);
  }
  if (request->hasParam("monitor_period", true)) {
    Serial.printf("monitor_period\n");
    param = request->getParam("monitor_period", true)->value();
    this->_storage->SetMonitorPeriod(param);
  }
  if (request->hasParam("build_period", true)) {
    Serial.printf("build_period\n");
    param = request->getParam("build_period", true)->value();
    this->_storage->SetBuildPeriod(param);
  }
  if (request->hasParam("password", true)) {
    Serial.printf("password\n");
    param = request->getParam("password", true)->value();
    if (param)
      this->_storage->SetJenkinsPassword(param);
  }
  if (request->hasParam("uri", true)) {
    Serial.printf("uri\n");
    param = request->getParam("uri", true)->value();
    this->_storage->SetUri(param);
  }
  
  this->_config = this->_storage->GetStoredConfig();
  this->SendIndex(request);
  //request->send(200, "text/plain", "Hello, POST: " + message);
  // request->send(SPIFFS, "/index.html", String(), false, std::bind(&ConfigurationServer::IndexTemplateProcessor, this, std::placeholders::_1));
}

String ConfigurationServer::IndexTemplateProcessor(const String& var) {
  if(var == "STATE")
    return String("Hello World!!!");
  if(var == "DEV_NAME")
    return String(this->_config.device_name);
  if(var == "MONITOR_PERIOD")
    return String(this->_config.monitor_period);
  if(var == "BUILD_PERIOD")
    return String(this->_config.build_period);
  if(var == "URI")
    return String(this->_config.uri);
  return String();
}

void ConfigurationServer::start(){
  this->_server->begin();
}

// Simple Firmware Update Form
  
  // server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request){
  //   shouldReboot = !Update.hasError();
  //   AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", shouldReboot?"OK":"FAIL");
  //   response->addHeader("Connection", "close");
  //   request->send(response);
  // },[](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
  //   if(!index){
  //     Serial.printf("Update Start: %s\n", filename.c_str());
  //     Update.runAsync(true);
  //     if(!Update.begin((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000)){
  //       Update.printError(Serial);
  //     }
  //   }
  //   if(!Update.hasError()){
  //     if(Update.write(data, len) != len){
  //       Update.printError(Serial);
  //     }
  //   }
  //   if(final){
  //     if(Update.end(true)){
  //       Serial.printf("Update Success: %uB\n", index+len);
  //     } else {
  //       Update.printError(Serial);
  //     }
  //   }
  // });
