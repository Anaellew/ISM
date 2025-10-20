#include <Arduino.h>
#include "application.h"
#include "communication.h"
#include "motor.h"

void setup() {
    Serial.begin(115200);
    app_init();
}

void loop() {
    //app_on_dt_event();
    if (Serial.available()>0){
        comm_receive_complete();
    }
}