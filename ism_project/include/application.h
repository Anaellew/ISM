#ifndef APPLICATION
#define APPLICATION

#include <stdint.h>

bool stop();
bool forward(uint16_t tension);
bool turn(uint16_t tension);

void on_dt_event();

#endif

