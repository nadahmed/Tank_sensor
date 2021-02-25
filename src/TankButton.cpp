#include <TankButton.h>

void TankButton::setup(){

    _button.begin();
    _button.read();
    if(_button.isPressed()) {
        if(_onInitPressCallBack != nullptr){
            
            _onInitPressCallBack();
        }
    }
    
}
void TankButton::loop(){
    _button.read();
    if (_button.wasPressed() )    // if the button was released, change the LED state
    {       
        if(_onPressCallBack != nullptr){
            _onPressCallBack();
        }

    }
    }

void TankButton::onPress(void (*onPressCallback)()){
    _onPressCallBack = onPressCallback;
}
void TankButton::onInitPress(void (*onInitPressCallback)()){
    _onInitPressCallBack = onInitPressCallback;
}