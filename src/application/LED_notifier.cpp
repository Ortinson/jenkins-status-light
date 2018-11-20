#include "LED_notifier.h"

LEDNotifier::LEDNotifier(uint32_t data_pin, uint32_t led_number) :
_data_pin(data_pin), _led_number(led_number) {

}

void LEDNotifier::Notify(jenkins_status_t status){
    //switch(status)

}