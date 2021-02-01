#if !defined(TANK_H)
#define TANK_H

class Tank
{
private:
    uint8_t* _pins;
    size_t _total_pins;
    /* data */
public:
    Tank(uint8_t*, size_t);
    void setup();
    uint8_t currentLevel();
    bool isFault();
    ~Tank();
};




#endif // TANK_H
