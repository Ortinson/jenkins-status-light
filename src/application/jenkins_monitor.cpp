#include "jenkins_monitor.h"

JenkinsMonitor::JenkinsMonitor(ConfigurationStorage* config_storage, LEDNotifier* notifier, uint period) :
    _config_storage(config_storage),
    _notifier(notifier),
    _period(period){
  this->_config_storage->SubscribeToConfigChange(std::bind(&JenkinsMonitor::OnConfigUpdate, this));
}

void JenkinsMonitor::Start() {
  // this->_myTicker.attach(this->_period, std::bind(&JenkinsMonitor::Monitor, this));  // TODO(Ortinson): Use timer to trigger Monitor()
}

void JenkinsMonitor::Stop() {
  // TODO(Ortinson): Use timer to trigger Monitor()
}

void JenkinsMonitor::OnConfigUpdate(){
  Serial.println("Monitor callback called!!!!");
  this->Monitor();
}

void JenkinsMonitor::Monitor(){
  lamp_config_t config = this->_config_storage->GetStoredConfig();
  jenkins_status_t status = this->GetJenkinsStatus();
  this->_notifier->Notify(config, status);
}

jenkins_status_t JenkinsMonitor::GetJenkinsStatus() {
  lamp_config_t config = this->_config_storage->GetStoredConfig();
  this->_http.begin(this->_client, config.uri);
  this->_http.setAuthorization(config.jenkins_user, config.jenkins_password);  //TODO get authorization from config
  
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
  const size_t capacity = 20000;
  DynamicJsonBuffer jsonBuffer(capacity);

  JsonObject& root = jsonBuffer.parseObject(response, 30);
  if (!root.success()) {
    Serial.println(F("Parsing failed!"));
    return SERVER_ERROR;
  }
  // Print values  // TODO(Ortinson): Remove
  Serial.println(F("Response:"));
  Serial.println(root["building"].as<char*>());
  Serial.println(root["result"].as<char*>());
  Serial.println(root["culprits"][0]["absoluteUrl"].as<char*>());
  Serial.println(root["culprits"][0]["fullName"].as<char*>());

  String building = root["building"].as<String>();
  String result = root["result"].as<String>();
  if (building == "true"){
    return RUNNING;
  }else if (result == "SUCCESS") {
    return SUCCESS;
  }else if (result == "FAILURE") {
    return FAILURE;
  }
  return SERVER_ERROR;
}