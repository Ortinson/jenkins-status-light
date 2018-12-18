#include "jenkins_monitor.h"

JenkinsMonitor::JenkinsMonitor(ConfigurationStorage* config_storage, LEDNotifier* notifier, Scheduler* scheduler) :
    _config_storage(config_storage),
    _notifier(notifier),
    _scheduler(scheduler){
  this->_config = this->_config_storage->GetStoredConfig();
  this->_config_storage->SubscribeToConfigChange(std::bind(&JenkinsMonitor::OnConfigUpdate, this));

  this->_t1 = new Task(_config->monitor_period * 1000, TASK_FOREVER, std::bind(&JenkinsMonitor::Monitor, this));
  this->_scheduler->addTask(*_t1);
  this->_t1->enable();
}

void JenkinsMonitor::OnConfigUpdate(){
  Serial.println("Monitor callback called!!!!");
  this->_t1->setInterval(_config->monitor_period * 1000);
  this->_t1->forceNextIteration();
}

void JenkinsMonitor::Monitor(){
  jenkins_status_t status = this->GetJenkinsStatus();
  this->_notifier->Notify(this->_config, status);
}

jenkins_status_t JenkinsMonitor::GetJenkinsStatus() {
  this->_http.begin(this->_config->uri);
  this->_http.setAuthorization(this->_config->jenkins_user, this->_config->jenkins_password);

  int httpCode = this->_http.GET();
  Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  if (httpCode != HTTP_CODE_OK) {
    this->_http.end();
    return SERVER_ERROR;
  }

  const String response = this->_http.getString();
  this->_http.end();
  return this->ParseResponse(response);
}

jenkins_status_t JenkinsMonitor::ParseResponse(const String response){
  const size_t capacity = 500;
  DynamicJsonBuffer jsonBuffer(capacity);

  JsonObject& root = jsonBuffer.parseObject(response, 30);
  if (!root.success()) {
    Serial.println(F("  Parsing failed!"));
    return SERVER_ERROR;
  }

  String building = root["building"].as<String>();
  String result = root["result"].as<String>();
  if (building == "true"){
    Serial.println("  Build is running.");
    return RUNNING;
  }else if (result == "SUCCESS") {
    Serial.println("  Build Successful.");
    return SUCCESS;
  }else if (result == "FAILURE") {
    Serial.println("  Build failed.");
    return FAILURE;
  }
  return SERVER_ERROR;
}