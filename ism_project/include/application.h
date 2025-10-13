#ifndef APPLICATION
#define APPLICATION

#include <stdint.h>
#include <stdbool.h>
#include <motor.h>
#include <communication.h>

static cfg_moteur M1;


bool stop();
bool forward(uint16_t tension);
bool turn(uint16_t tension);
bool existe_message();

void on_dt_event();

#endif

