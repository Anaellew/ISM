#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>

typedef struct message_t{
    uint16_t code;
    uint16_t timeout;
    uint16_t voltage;
} message_t;

int16_t code_stop = 0;
int16_t code_forward = 1;
int16_t code_turn = 2;

message_t receive();

bool send(message_t msg);

bool compare_code(char str1[24], char str2[24]);

#endif