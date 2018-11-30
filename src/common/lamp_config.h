#ifndef COMMON_LAMP_CONFIG_H_
#define COMMON_LAMP_CONFIG_H_

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <stdint.h>

typedef enum class {
    ON,
    OFF,
    Flash,
    Pulse,
    Rainbow,
} animation_t;

typedef enum  {
    RUNNING,
    SUCCESS,
    FAILURE,
    SERVER_ERROR,
    JENKINS_STATUS_NR_ITEMS,
} jenkins_status_t;

struct Color {
  size_t red, green, blue;  // TODO(Ortinson): Check if there is old code using uint8_t
};

struct Notification {
    jenkins_status_t jenkins_status;
    Color color;
    animation_t animation;
    uint32_t period;
};

typedef struct{
  Notification notification_list[JENKINS_STATUS_NR_ITEMS];
  uint32_t monitor_period;
  uint32_t build_period;
  char jenkins_user[256];
  char jenkins_password[256];
  char uri[256];
  char device_name[128];
  uint32_t valid_config;
} lamp_config_t;

#endif
