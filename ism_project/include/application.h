#ifndef APPLICATION
#define APPLICATION

#include <stdint.h>
#include <stdbool.h>
#include <motor.h>
#include <communication.h>

typedef enum state_motor_t {
    IDLE,
    RECEIVING,
    STOP,
    FORWARD,
    TURN
}state_motor_t;

bool stop();
bool forward(uint16_t tension);
bool turn(uint16_t tension);
bool existe_message();

void on_dt_event();

#endif

