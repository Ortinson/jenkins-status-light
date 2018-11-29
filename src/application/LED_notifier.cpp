#include "LED_notifier.h"
#define DATA_PIN 5 // FastLED requires this definition

LEDNotifier::LEDNotifier(){
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(&this->_leds[0], 16);
}

void LEDNotifier::Notify(lamp_config_t* config, jenkins_status_t status){
    Notification* n = NULL;
    for (int i = 0; i < JENKINS_STATUS_NR_ITEMS; i++){
        if (config->notification_list[i].jenkins_status == status) {
            n = &config->notification_list[i];
            break;
        }
    }

    if (n == NULL) {
        printf("status %d not found in configuration", status);
        return;
    }

    this->_animation_color = n->color;
    this->_animation_period = n->period;
    this-> BindAnimation(n->animation);
}   

void LEDNotifier::BindAnimation(animation_t animation) {
    void (LEDNotifier::*function)(unsigned long, Color, unsigned long);
    switch (animation) {
    case animation_t::ON:
        function = &LEDNotifier::On;
        break;
    case animation_t::OFF:
        function = &LEDNotifier::Off;
        break;
    case animation_t::Flash:
        function = &LEDNotifier::Flash;
        break;
    case animation_t::Pulse:
        function = &LEDNotifier::Pulse;
        break;
    case animation_t::Rainbow:
        function = &LEDNotifier::Rainbow;
        break;
    }

    this->_animation_f = std::bind(function, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);    
}

void LEDNotifier::Cycle(){
    this->_animation_f(millis(), this->_animation_color, this->_animation_period);
}

void LEDNotifier::Flash(unsigned long tim, Color color, unsigned long period){ 
    static unsigned long next_flash = 0;
    static bool onoff = true;
    if (next_flash < tim){
        if (onoff){
            this->ShowColor(color);
        }else{
            this->Off();
        }
        onoff = !onoff;
        FastLED.show();
    next_flash = tim + period * 1000;
    }    
}

void LEDNotifier::Pulse(unsigned long tim, Color color, unsigned long period){ 
    static unsigned long cycle_start = 0;
    
    if (tim > cycle_start + period * 1000){
        cycle_start = tim;
    }

    unsigned long elapsed_time = tim - cycle_start;
    double pulse = 1;
    if (elapsed_time != 0)
        pulse = (double)elapsed_time / ((double)period * (double)1000) ;
    pulse = (sin(pulse * (double)6.28) + (double)1)/(double)2;

    color.red = static_cast<uint8_t>(color.red*pulse);
    color.green = static_cast<uint8_t>(color.green*pulse);
    color.blue = static_cast<uint8_t>(color.blue*pulse);
    
    this->ShowColor(color);
}

void LEDNotifier::On(unsigned long tim, Color color, unsigned long period) {
    this->ShowColor(color);
}

void LEDNotifier::Off(unsigned long tim, Color color, unsigned long period) {
    FastLED.clear();
}

void LEDNotifier::Off() {
    FastLED.clear();
}

void LEDNotifier::Rainbow(unsigned long tim, Color color, unsigned long period) {
    FastLED.clear(); // TODO(Ortinson): Implement
}

void LEDNotifier::ShowColor(Color color) {
    for (unsigned int i = 0; i < this->_led_number; i++ ){
        this->_leds[i] = CRGB(color.green, color.red, color.blue);
    }
    FastLED.show();
}

void LEDNotifier::ShowColor(uint8_t r, uint8_t g, uint8_t b) {
    Color color = {r, g, b};
    this->ShowColor(color);
}
