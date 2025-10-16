#include <Arduino.h>
#include "communication.h"

void test_communication(){
    if (Serial.available() > 0){
        send(receive());
    }
}