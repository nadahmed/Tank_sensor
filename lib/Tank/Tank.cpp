#include <Arduino.h>
#include <Tank.h>

Tank::Tank(uint8_t* pins, size_t total_pins)
{
    _pins = pins;
    _total_pins = total_pins;
}

void Tank::setup(){
    for(uint8_t i=0; i < _total_pins; i++){
        pinMode(_pins[i], INPUT);
    }
}

uint8_t Tank::currentLevel(){
    uint8_t _level = 0;
    for(uint8_t i; i < _total_pins; i++){
        _level += digitalRead(_pins[i]);
    }
    return _level;
}

bool Tank::isFault(){
    for(uint8_t i=0; i < _total_pins-1; i++){
        if(digitalRead(_pins[i+1]) < digitalRead(_pins[i])) {
            return true;
        }
    }
    return false;
}


Tank::~Tank()
{
}