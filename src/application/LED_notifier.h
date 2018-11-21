#ifndef LED_NOTIFIER_H_
#define LED_NOTIFIER_H_

#define NUM_LED 16

#include <stdint.h>
#include "common/lamp_config.h"
#include <FastLED.h>

// TODO (Ortinson): Define notification interface based on this driver.
// We just want to notify the state of the jenkins build. The way this is
// achieved do not matter.

class LEDNotifier {
public:
  LEDNotifier();
  void Notify(lamp_config_t config, jenkins_status_t status);  //TODO (Ortinson)
  void Cycle();

private:
  void Blink(unsigned long time, Color color, unsigned long period);
  void On(unsigned long time, Color color, unsigned long period);
  void Fade(unsigned long time, Color color, unsigned long period);
  void Off(unsigned long time, Color color, unsigned long period);
  void Off();
  void ShowColor(Color color);
  void ShowColor(uint8_t r, uint8_t g, uint8_t b);

  unsigned char _data_pin;
  size_t _led_number = NUM_LED;
  Color _animation_color;
  unsigned long _animation_period;
  CRGB _leds[NUM_LED];
  std::function<void(unsigned long, Color, unsigned long)> _animation_f = NULL;
};

#endif // LED_NOTIFIER_H_
