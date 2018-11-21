#include "LED_notifier.h"
#define DATA_PIN 5 // FastLED requires this definition
LEDNotifier::LEDNotifier(){
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(&this->_leds[0], 16);
    FastLED.clear();
    FastLED.show();
}

// Todo(Ortinson): select function to call based on config file
void LEDNotifier::Notify(lamp_config_t config, jenkins_status_t status){
    Serial.printf("Status: %d", status);
    switch(status){
        case RUNNING:
            this->_animation_color = config.build_running.color;
            this->_animation_period = config.build_running.period;
            this->_animation_f = std::bind(&LEDNotifier::Blink, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
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
    Serial.printf("red:%d, g:%d, b:%d, period: %d\n",this->_animation_color.red, this->_animation_color.green, this->_animation_color.blue, this->_animation_period);
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
        this->_leds[i] = CRGB(color.green, color.red, color.blue);
    }
    FastLED.show();

}
