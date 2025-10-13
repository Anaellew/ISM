#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>

typedef struct message{
    uint16_t code;
    uint16_t timeout;
    uint16_t tension;
} message;

message receive();

bool send(message msg);

#endif