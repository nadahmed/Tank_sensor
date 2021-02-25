#if !defined(TANK_BUTTON_H)
#define TANK_BUTTON_H
#include <Arduino.h>
#include <JC_Button.h>

class TankButton
{
private:

    Button _button;
    void (*_onPressCallBack)();
    void (*_onInitPressCallBack)();

public:
    TankButton(const byte pin):
    // button connected from pin 2 to ground, 25ms debounce, pullup enabled, logic inverted
    _button(pin, 50, false, true){}

    void setup();
    void loop();
    void onPress(void (*)());
    void onInitPress(void (*)());
};

#endif