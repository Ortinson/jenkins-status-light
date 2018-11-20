#include "jenkins_monitor.h"

JenkinsMonitor::JenkinsMonitor(ConfigurationStorage* config_storage) :
  _config_storage(config_storage){
    _config_storage->SubscribeToConfigChange(std::bind(&JenkinsMonitor::OnConfigUpdate, this));
}
// (&ConfigurationServer::SendIndex, this, std::placeholders::_1)
void JenkinsMonitor::OnConfigUpdate(){
  Serial.println("Monitor callback called!!!!");
}

void JenkinsMonitor::Start(){
  //Set timer to call to check function
}

void JenkinsMonitor::Monitor(){
  this->GetBranchStatus();
}

int JenkinsMonitor::GetBranchStatus() {
  // Al the magicto get the status
  return -1;
}