#include "LED_notifier.h"
#define DATA_PIN 5 // FastLED requires this definition
LEDNotifier::LEDNotifier(){
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(&this->_leds[0], 16);
}

// Todo(Ortinson): select function to call based on config file
void LEDNotifier::Notify(lamp_config_t config, jenkins_status_t status){
    Serial.printf("Status: %d", status);
    switch(status){
        case RUNNING:
            this->_animation_color = config.build_running.color;
            this->_animation_period = config.build_running.period;
            this->_animation_f = std::bind(&LEDNotifier::Fade, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
            break;
        case SUCCESS:
            this->_animation_color = config.build_ok.color;
            this->_animation_period = config.build_ok.period;
            this->_animation_f = std::bind(&LEDNotifier::On, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
            break;
        case FAILURE:
            this->_animation_color = config.build_err.color;
            this->_animation_period = config.build_err.period;
            this->_animation_f = std::bind(&LEDNotifier::Blink, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        case SERVER_ERROR:
            this->_animation_color = config.server_down.color;
            this->_animation_period = config.server_down.period;
            this->_animation_f = std::bind(&LEDNotifier::Blink, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    }
}   

void LEDNotifier::Cycle(){
    this->_animation_f(millis(), this->_animation_color, this->_animation_period);
}

void LEDNotifier::Blink(unsigned long tim, Color color, unsigned long period){ 
    static unsigned long next_blink = 0;
    static bool onoff = true;
    if (next_blink < tim){
        if (onoff){
            this->ShowColor(color);
        }else{
            this->Off();
        }
        onoff = !onoff;
        FastLED.show();
    next_blink = tim + period * 1000;
    }    
}

void LEDNotifier::Fade(unsigned long tim, Color color, unsigned long period){ 
    static unsigned long cycle_start = 0;
    
    if (tim > cycle_start + period * 1000){
        cycle_start = tim;
    }

    unsigned long elapsed_time = tim - cycle_start;
    double fade = 1;
    if (elapsed_time != 0)
        fade = (double)elapsed_time / ((double)period * (double)1000) ;
    fade = (sin(fade * (double)6.28) + (double)1)/(double)2;

    color.red = static_cast<uint8_t>(color.red*fade);
    color.green = static_cast<uint8_t>(color.green*fade);
    color.blue = static_cast<uint8_t>(color.blue*fade);
    
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

void LEDNotifier::ShowColor(Color color) {
    for (unsigned int i = 0; i < this->_led_number; i++ ){
        this->_leds[i] = CRGB(color.red, color.green, color.blue);
    }
    FastLED.show();
}

void LEDNotifier::ShowColor(uint8_t r, uint8_t g, uint8_t b) {
    Color color = {r, g, b};
    this->ShowColor(color);
}
