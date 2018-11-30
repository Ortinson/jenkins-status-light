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

  this->_server->on("/", HTTP_POST, std::bind(&ConfigurationServer::UpdateConfig, this, std::placeholders::_1));
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
    param = request->getParam("dev_name", true)->value();
    this->_storage->SetDeviceName(param);
  }
  if (request->hasParam("monitor_period", true)) {
    param = request->getParam("monitor_period", true)->value();
    this->_storage->SetMonitorPeriod(param);
  }
  if (request->hasParam("build_period", true)) {
    param = request->getParam("build_period", true)->value();
    this->_storage->SetBuildPeriod(param);
  }
  if (request->hasParam("user", true)) {
    param = request->getParam("user", true)->value();
    if (param)
      this->_storage->SetJenkinsUser(param);
  }
  if (request->hasParam("password", true)) {
    param = request->getParam("password", true)->value();
    if (param.length() != 0)
      this->_storage->SetJenkinsPassword(param);
  }
  if (request->hasParam("uri", true)) {
    param = request->getParam("uri", true)->value();
    this->_storage->SetUri(param);
  }

  if (request->hasParam("success_color", true)) {
    param = request->getParam("success_color", true)->value();
    this->_storage->SetSuccessColor(param);
  }

  if (request->hasParam("failure_color", true)) {
    param = request->getParam("failure_color", true)->value();
    this->_storage->SetFailureColor(param);
  }

  if (request->hasParam("running_color", true)) {
    param = request->getParam("running_color", true)->value();
    this->_storage->SetRunningColor(param);
  }

  if (request->hasParam("error_color", true)) {
    param = request->getParam("error_color", true)->value();
    this->_storage->SetErrorColor(param);
  }
  
  this->SendIndex(request);
}

String ConfigurationServer::IndexTemplateProcessor(const String& var) {
  if(var == "DEV_NAME")
    return String(this->_config->device_name);
  if(var == "MONITOR_PERIOD")
    return String(this->_config->monitor_period);
  if(var == "BUILD_PERIOD")
    return String(this->_config->build_period);
  if(var == "URI")
    return String(this->_config->uri);
  if(var == "USER")
    return String(this->_config->jenkins_user);
  if(var == "SUCCESS_COLOR")
    return ::ColorToHTML(this->_config->notification_list[0].color); //TODO(Ortinson): substitute magic numbers with SelectNotification
  if(var == "FAILURE_COLOR")
    return ::ColorToHTML(this->_config->notification_list[1].color);
  if(var == "RUNNING_COLOR")
    return ::ColorToHTML(this->_config->notification_list[2].color);
  if(var == "ERROR_COLOR")
    return ::ColorToHTML(this->_config->notification_list[3].color);
  return String();
}

void ConfigurationServer::Start(){
  this->_server->begin();
}
