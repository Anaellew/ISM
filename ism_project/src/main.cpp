#include <Arduino.h>
#include "application.h"
#include "communication.h"
#include "motor.h"

void setup() {
    Serial.begin(9600);
}

void loop() {
    on_dt_event();
}