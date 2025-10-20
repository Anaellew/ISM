#include <Arduino.h>
#include "application.h"
#include "communication.h"
#include "motor.h"

void setup() {
    Serial.begin(115200);
}

void loop() {
    app_on_dt_event();
}