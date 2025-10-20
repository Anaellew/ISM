#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdint.h>
#include <stdbool.h>
#include <motor.h>
#include <communication.h>

typedef enum state_motor_t {
    STOP,
    FORWARD,
    TURN
}state_motor_t;

typedef enum state_communication_t {
    IDLE,
    RECEIVING
}state_communication_t;

typedef struct table_cmd {
    const char* table[3];
    uint16_t len;
} table_cmd;
table_cmd commandes = {{"STOP", "FORWARD", "TURN"}, 3};

bool app_stop();
bool app_forward(uint16_t voltage);
bool app_turn(uint16_t voltage);
bool app_check_char();

void app_on_dt_event();

#endif

