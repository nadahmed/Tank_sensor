#if !defined(CONFIG_H)
#define CONFIG_H

// TANK_ID:
// LOWER - 0x02
// UPPER - 0x03
// CUSTOM - 0x04


#define ENABLE_UPPER_TANK
// #define ENABLE_LOWER_TANK

/* Incase of custom tank uncomment 3 lines below */
// #define ENABLE_CUSTOM_TANK
// #define TANK_ID 0x04
// #define NO_OF_LEVELS 4

// Time(in ms) it takes for the sensor to detect change
#define SENSOR_DETECTION_TIME 1000

#if defined(ENABLE_LOWER_TANK)
    #define TANK_ID 0x02
    #define NO_OF_LEVELS 2
#elif defined(ENABLE_UPPER_TANK)
    #define TANK_ID 0x03
    #define NO_OF_LEVELS 3
#endif
// Level 1 is low
// Levels are detected from low to high until NO_OF_SENSORS
#define SENSOR_LEVEL_1 A0
#define SENSOR_LEVEL_2 A1
#define SENSOR_LEVEL_3 A2
#define SENSOR_LEVEL_4 A3

#define BUTTON A5

// 1-wire PJON Softwarebitbang pin

#define COMM_PIN 2

#define BAUD_RATE 9600

#endif // CONFIG_H

