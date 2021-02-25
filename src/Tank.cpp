#include <Tank.h>

void Tank::_checkWaterLevel()
{
    uint8_t _level = 0;
    static uint8_t temp_level = -1;

    for (uint8_t i = 0; i < NO_OF_LEVELS; i++)
    {
        _level += _values[i];
    }

    if (temp_level != _level)
    {
        data.current_level=_level;

        
        
        if (_onLevelChangeCallBack != nullptr) {
            _onLevelChangeCallBack(_level);
            _change = true;
        }
        
        
        temp_level = _level;
    }
}

bool Tank::_checkFault()
{
    bool _fault = false;
    static bool temp = false;
    for (uint8_t i = NO_OF_LEVELS-1; i > 0; i--)
    {
        if (!(_values[i] <= _values[i-1]))
        {
            _fault = _fault || true;
        }
    }

    if (_fault != temp)
    {
        data.fault = _fault;
        _change = true;

        if (_fault){
            if(_onFaultCallBack != nullptr){
                _onFaultCallBack();
            }
            
        }

        temp = _fault;
    }

    return _fault;
}


void Tank::setup()
{
    // Logger::setOutputFunction(TankLogger);

    
}

void Tank::loop()
{
    for (uint8_t i = 0; i < NO_OF_LEVELS; i++)
    {
        this->_values[i] = _sensor[i].read();
        data.states[i] = this->_values[i];
    }
    
    _checkWaterLevel();
    _checkFault();
    if(_change){
        if(_onChangeCallBack != nullptr){
            _onChangeCallBack();
        }
        _change = false;
    }
}

void Tank::onChange(void (*onChangeCallback)()) {
    this->_onChangeCallBack = onChangeCallback;
}

void Tank::onLevelChange(void (*onLevelChangeCallback)(uint8_t level)) {
    this->_onLevelChangeCallBack = onLevelChangeCallback;
}

void Tank::onFault(void (*onFaultCallBack)()){
    this->_onFaultCallBack = onFaultCallBack;
}

void Tank::print(){
        for(uint8_t i=0; i < NO_OF_LEVELS; i++){
            Serial.print(data.states[i]);
            Serial.print(F("\t"));
        }
        Serial.print(data.current_level);
        Serial.print(F("\t"));
        Serial.println(data.fault);
}

Tank::~Tank()
{
}