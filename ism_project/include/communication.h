#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>

typedef struct message_t{
    uint16_t code;
    uint16_t timeout;
    uint16_t voltage;
} message_t;

message_t receive();

void send(message_t msg);

bool compare_code(const char str1[24], const char str2[24]);

#endif