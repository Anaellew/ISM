#ifndef APPLICATION
#define APPLICATION

#include <stdint.h>

bool stop();
bool forward(uint16_t tension);
bool turn(uint16_t tension);

bool message();
void on_dt_event();

#endif
