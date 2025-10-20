#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>

#define MAX_WORD_LEN 24
#define MAX_WORDS_NB 3

typedef struct message_t{
    uint16_t code;
    uint16_t timeout;
    uint16_t voltage;
} message_t;

message_t comm_receive_complete();

bool compare_code(const char str1[24], const char str2[24]);

#endif