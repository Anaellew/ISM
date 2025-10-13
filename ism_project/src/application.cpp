#include "application.h"
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>

static state_motor_t state_motor;

static cfg_motor M1 = {34, 35, 12};
static cfg_motor M2 = {};
static uint16_t timeout;
static uint16_t start_time;


bool stop(){
    return control_motor(M1, 0) && control_motor(M2, 0);
}

bool forward(uint16_t voltage){
    return control_motor(M1, voltage) && control_motor(M2, -voltage);
}

bool turn(uint16_t voltage){
    return control_motor(M1, voltage);
}

bool check_msg(){
    return (Serial.available() > 0);
}

void on_dt_event(){
    switch (state_motor){
        case IDLE:
            if (check_msg()) state_motor = RECEIVING;
        break;
        case RECEIVING:
            message_t msg = receive();
            timeout = msg.timeout;
            start_time = millis();
            if (msg.code == 0) state_motor = STOP;
            if (msg.code == 1) state_motor = FORWARD;
            if (msg.code == 2) state_motor = TURN;
        break;
        case STOP:
            stop();
            if(check_msg()) state_motor = RECEIVING;
        break;
        case FORWARD:
            forward(msg.voltage);
            if(millis()- start_time > timeout) state_motor = IDLE;
            if(check_msg()) state_motor = RECEIVING;
        break;
        case TURN:
            turn(msg.voltage);
            if(millis()- start_time > timeout) state_motor = IDLE;
            if(check_msg()) state_motor = RECEIVING;
        break;
    } 
}