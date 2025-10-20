#include "motor.h"
#include "application.h"

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>

static state_motor_t state_motor;
static state_communication_t state_communication;

static cfg_motor M1 = {34, 35, 12};
static cfg_motor M2 = {37, 36, 8};
static uint16_t timeout;
static uint16_t start_time;

bool app_stop(){
    return control_motor(M1, 0) && control_motor(M2, 0);
}

bool app_forward(uint16_t voltage){
    return control_motor(M1, voltage) && control_motor(M2, voltage);
}

bool app_turn(uint16_t voltage){
    return control_motor(M1, voltage) && control_motor(M2, -voltage);
}

bool app_check_char(){
    return (Serial.available() > 0);
}

void app_on_dt_event(){
    message_t msg;
    switch (state_motor){
        case STOP:
            app_stop();
            if(app_check_char()) state_communication = RECEIVING;
        break;
        case FORWARD:
            app_forward(msg.voltage);
            if(millis()- start_time > timeout){
                state_communication = IDLE;
                state_motor = STOP;
            }
            if(app_check_char()) state_communication = RECEIVING;
        break;
        case TURN:
            app_turn(msg.voltage);
            if(millis()- start_time > timeout){
                state_communication = IDLE;
                state_motor = STOP;
            }
            if(app_check_char()) state_communication = RECEIVING;
        break;
    } 

    switch (state_communication){
        case IDLE:
            if (app_check_char()) state_communication = RECEIVING;
        break;
        case RECEIVING:
            msg = comm_receive();
            timeout = msg.timeout;
            if (msg.code == 0) state_motor = STOP;
            if (msg.code == 1) {
                state_motor = FORWARD;
                start_time = millis();
            }
            if (msg.code == 2){
                state_motor = TURN;
                start_time = millis();
            } 
            state_communication = IDLE;
        break;
    }
}

void app_init(){
    state_motor = STOP;
    state_communication = IDLE;
}