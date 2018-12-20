#include "LED_notifier.h"
#define DATA_PIN 5 // FastLED requires this definition

LEDNotifier::LEDNotifier(){
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(&this->_leds[0], 16);
    this->BindAnimation(animation_t::OFF);
}

void LEDNotifier::Notify(lamp_config_t* config, jenkins_status_t status){
    Notification* n = ::SelectNotification(config, status);

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
    this->Off();
}

void LEDNotifier::Off() {
    FastLED.clear();
    FastLED.show();
}

void LEDNotifier::Rainbow(unsigned long tim, Color color, unsigned long period) {
    static unsigned long cycle_start = 0;

    if (tim > cycle_start + period * 1000){
        cycle_start = tim;
    }
    double cycle_position = (tim - cycle_start) / ((double) period*1000);

    // RED
    color.red = static_cast<uint8_t>(255 * this->CalculateTriangleBrightness(cycle_position));

    // GREEN
    double cycle_position_mod = cycle_position;
    if (cycle_position_mod > (double)1/3) {
        cycle_position_mod = cycle_position_mod - (double)1/3;
    } else {
        cycle_position_mod = cycle_position_mod + (double)2/3;
    }
    color.green = static_cast<uint8_t>(255 * this->CalculateTriangleBrightness(cycle_position_mod));

    // BLUE
    cycle_position_mod = cycle_position;
    if (cycle_position_mod < (double)2/3) {
        cycle_position_mod = cycle_position_mod + (double)1/3;
    } else {
        cycle_position_mod = cycle_position_mod - (double)2/3;
    }
    color.blue = static_cast<uint8_t>(255 * this->CalculateTriangleBrightness(cycle_position_mod));

    this->ShowColor(color);
}

double LEDNotifier::CalculateTriangleBrightness(double cycle_position) {
    double val = 1;
    if (cycle_position < ((double)1/3)) {
        val = cycle_position * 3;
    } else if (cycle_position > ((double)2/3)) {
        val = 0;
    } else {
        val = 1 - (cycle_position - (double)1/3) * 3;
    }
    return val;
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
