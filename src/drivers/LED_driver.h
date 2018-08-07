#ifndef DRIVERS_LED_DRIVER_H_
#define DRIVERS_LED_DRIVER_H_

#include <stdint.h>
// #include fastled

class LEDDriver {
public:
  LEDDriver(uint32_t data_pin, uint32_t led_number);

private:
  uint32_t _data_pin;
  uint32_t _led_number;
};

#endif // DRIVERS_LED_DRIVER_H_
