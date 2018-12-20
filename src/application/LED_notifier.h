#ifndef LED_NOTIFIER_H_
#define LED_NOTIFIER_H_

#define NUM_LED 16

#include <stdint.h>
#include "common/lamp_config.h"
#include "common/utils.h"
#include <FastLED.h>

class LEDNotifier {
public:
  LEDNotifier();
  void Notify(lamp_config_t* config, jenkins_status_t status);
  void Cycle();

private:
  void Flash(unsigned long time, Color color, unsigned long period);
  void Pulse(unsigned long time, Color color, unsigned long period);
  void Rainbow(unsigned long time, Color color, unsigned long period);
  void On(unsigned long time, Color color, unsigned long period);
  void Off(unsigned long time, Color color, unsigned long period);
  void Off();
  void ShowColor(Color color);
  void ShowColor(uint8_t r, uint8_t g, uint8_t b);
  void BindAnimation(animation_t animation);
  static double CalculateTriangleBrightness(double cycle_position);

  unsigned char _data_pin;
  size_t _led_number = NUM_LED;
  Color _animation_color;
  unsigned long _animation_period;
  CRGB _leds[NUM_LED];
  std::function<void(unsigned long, Color, unsigned long)> _animation_f = NULL;
};

#endif // LED_NOTIFIER_H_
