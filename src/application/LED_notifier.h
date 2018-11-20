#ifndef LED_NOTIFIER_H_
#define LED_NOTIFIER_H_

#include <stdint.h>
// #include fastled

// TODO (Ortinson): Define notification interface based on this driver.
// We just want to notify the state of the jenkins build. The way this is
// achieved do not matter.

class LEDNotifier {
public:
  LEDNotifier(uint32_t data_pin, uint32_t led_number);
  void Notify();  //TODO (Ortinson)

private:
  uint32_t _data_pin;
  uint32_t _led_number;
};

#endif // LED_NOTIFIER_H_
