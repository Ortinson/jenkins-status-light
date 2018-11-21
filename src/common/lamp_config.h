#ifndef COMMON_LAMP_CONFIG_H_
#define COMMON_LAMP_CONFIG_H_

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <stdint.h>

typedef enum  {
    ON,
    OFF,
    Flash,
    Pulse,
    Fade,
    Rainbow,
} animation_t;

typedef enum  {
    RUNNING,
    SUCCESS,
    FAILURE,
    SERVER_ERROR,

} jenkins_status_t;

struct Color {
  uint8_t red, green, blue;
};

struct Notification {
    Color color;
    animation_t animation;
    uint32_t period;
};

typedef struct{
  Notification build_ok;
  Notification build_err;
  Notification build_running;
  Notification build_not_found;
  Notification server_down;
  uint32_t monitor_period;
  uint32_t build_period;
  char jenkins_user[256];
  char jenkins_password[256];
  char uri[256];
  char device_name[128];
  uint32_t valid_config;
} lamp_config_t;

#endif
