#ifndef MOTOR
#define MOTOR

#include <stdint.h>

typedef struct cfg_motor {
		uint16_t BI1;
		uint16_t BI2;
		uint16_t PWM;
	} cfg_motor;

bool control_motor(cfg_motor M, int16_t voltage);

void init2();

void test();

void motor_coast(cfg_motor M);

#endif 