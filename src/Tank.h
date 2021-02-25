#if !defined(TANK_H)
#define TANK_H

#include <Arduino.h>
#include <Logger.h>
#include <Debounce.h>
#include <Configuration.h>

class Tank
{
private:
    
    uint8_t* _values = (uint8_t*) malloc(NO_OF_LEVELS*sizeof(uint8_t));
    Debounce* _sensor = (Debounce*) malloc(NO_OF_LEVELS*sizeof(Debounce));
    bool _change = false;

    
    
    enum Frame {
        START = 0,
        HEARTBEAT,
        STATUS,
        ERROR
    };

    void status(Frame);
    void _checkWaterLevel();
    bool _checkFault();

    void (*_onChangeCallBack)();
    void (*_onLevelChangeCallBack)(uint8_t level);
    void (*_onFaultCallBack)();

public:

    struct Data
        {
            uint8_t total_levels = NO_OF_LEVELS;
            uint8_t states[4];
            uint8_t current_level=0;
            bool fault=false;
        };
        

    Data data;

    Tank(uint8_t *pins, long unsigned int debounce_ms)
    {
        for(uint8_t i = 0; i<NO_OF_LEVELS; i++){
            _sensor[i] = Debounce(pins[i], debounce_ms);
        }
    }
    void setup();
    void loop();
    
    void onChange(void(*)());
    void onLevelChange(void (*)(uint8_t));
    void onFault(void (*)());
    void print();
    ~Tank();
};




#endif // TANK_H
