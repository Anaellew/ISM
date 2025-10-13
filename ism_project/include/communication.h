#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>

typedef struct message_t{
    uint16_t code;
    uint16_t timeout;
    uint16_t tension;
} message_t;

message_t receive();

bool send(message_t msg);

#endif