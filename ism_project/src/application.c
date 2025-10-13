#include "application.h"
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>

enum state_motor_t {
    IDLE,
    RECEIVING,
    STOP,
    FORWARD,
    TURN,
};

state_motor_t state_motor;

static cfg_moteur M1;
static cfg_moteur M2;
uint16_t timeout;
uint16_t tps_debut;


bool stop(){
    return controler_moteur(M1, 0) && controler_moteur(M2, 0);
}

bool forward(uint16_t tension){
    return controler_moteur(M1, tension) && controler_moteur(M2, -tension);
}

bool turn(uint16_t tension){
    return controler_moteur(M1, tension);
}

bool existe_message(){
    return (Serial.available() > 0);
}

void on_dt_event(){
    switch (state_motor){
        case IDLE:
            if (existe_message()) state_motor = RECEIVING;
        break;
        case RECEIVING:
            message_t msg = receive();
            timeout = msg.timeout;
            tps_debut = millis();
            if (msg.code == 0) state_motor = STOP;
            if (msg.code == 1) state_motor = FORWARD;
            if (msg.code == 2) state_motor = TURN;
        break;
        case STOP:
            stop();
            if(existe_message()) state_motor = RECEIVING;
        break;
        case FORWARD:
            forward(msg.tension);
            if(millis()-tps_debut > timeout) state_motor = IDLE;
            if(existe_message()) state_motor = RECEIVING;
        break;
        case TURN:
            turn(msg.tension);
            if(millis()-tps_debut > timeout) state_motor = IDLE;
            if(existe_message()) state_motor = RECEIVING;
        break;
    } 
}