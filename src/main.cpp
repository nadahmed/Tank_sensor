#include <Arduino.h>
#include <Configuration.h>
#include <Tank.h>

uint8_t LEVEL_PINS[] = { SENSOR_LEVEL_1, SENSOR_LEVEL_2, SENSOR_LEVEL_3, SENSOR_LEVEL_4 };

Tank upper_tank(LEVEL_PINS, NO_OF_LEVELS);

void setup() {
    Serial.begin(9600);
    upper_tank.setup();
}

void loop() {
    
    Serial.print(upper_tank.isFault());
    Serial.println("");
    delay(1000);
  // put your main code here, to run repeatedly:
}