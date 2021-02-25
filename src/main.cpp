#define SWBB_MODE 1

#include <Arduino.h>
#include <Configuration.h>
#include <Logger.h>
#include <Tank.h>
#include <TankButton.h>
#include <PJONSoftwareBitBang.h>

PJONSoftwareBitBang bus(TANK_ID);

uint8_t LEVEL_PINS[] = { SENSOR_LEVEL_1, SENSOR_LEVEL_2, SENSOR_LEVEL_3, SENSOR_LEVEL_4 };

Tank upper_tank(LEVEL_PINS, SENSOR_DETECTION_TIME);

bool isUpdated = false;

TankButton button(BUTTON);

void(* resetFunc) (void) = 0; //declare reset function @ address 0

enum INCOMING {
    RESET = 0,
    SEND_DATA,
    SEND_UPDATED_DATA,
};

void receiver_function(uint8_t *payload, uint16_t length, const PJON_Packet_Info &info) {
  Logger::verbose("RECIEVED MSG");
  if(payload[0]==INCOMING::RESET){
      resetFunc();
  } else if(payload[0]==INCOMING::SEND_DATA){
    bus.reply(&upper_tank.data, sizeof(upper_tank.data));
  } else if(payload[0]==INCOMING::SEND_UPDATED_DATA){
        if (isUpdated){
            bus.reply(&upper_tank.data, sizeof(upper_tank.data));
        } else {
            byte msg = 0;
            bus.reply(&msg, sizeof(msg));
        }

        isUpdated = false;
  }
};

void setup() {
    Serial.begin(BAUD_RATE);
    bus.strategy.set_pin(COMM_PIN);
    bus.set_communication_mode(PJON_HALF_DUPLEX);
    bus.set_receiver(receiver_function);
    bus.begin();

    Logger::setLogLevel(Logger::VERBOSE);

    Logger::verbose("TANK: ", "Initializing...");

    char log[30];
    snprintf(log, sizeof(log), "Total levels are %d.", NO_OF_LEVELS);
    Logger::verbose("TANK: ", log);

    upper_tank.onChange([](){
        if (Logger::getLogLevel() <= Logger::NOTICE){
            Serial.print("[");
            Serial.print(Logger::asString(Logger::NOTICE));
            Serial.print("] : TANK: ");
            upper_tank.print();
        }
        isUpdated = true;
        // if(isInitialized){
        //     bus.send(1, &upper_tank.data, sizeof(upper_tank.data));
        // } else {
        //     byte msg = Message::READY;
        //     bus.send(1, &msg, sizeof(byte));
        //     isInitialized = true;
        // }
    });
    upper_tank.onLevelChange([](uint8_t level){
        char log[30];
        snprintf(log, sizeof(log), "Current water level is %d.", level);
        Logger::verbose("TANK: ", log);
    });

    upper_tank.onFault([](){
        Logger::error("TANK: ", "Fault detected!");
    });

    upper_tank.setup();

    Logger::verbose("BUTTON: ", "Initializing...");

    button.onPress([](){
        Logger::verbose("BUTTON: ", "Was Pressed");
        // bus.send(1, &upper_tank.data, sizeof(upper_tank.data));
    });

    button.onInitPress([](){
        Logger::verbose("BUTTON: ", "Pressed on init.");
    });

    button.setup();

}

void loop() {
    upper_tank.loop();
    button.loop();
    bus.update();
    bus.receive();
}