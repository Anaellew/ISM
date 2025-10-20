#include <Arduino.h>
#include "communication.h"
#include "application.h"


static int16_t code_stop = 0;
static int16_t code_forward = 1;
static int16_t code_turn = 2;

message_t comm_receive_complete(){
    message_t msg;
    char mots[3][24] = {0};
    char c;
    int16_t i = 0;
    int16_t j = 0;
    int16_t wordCount = 0;

    // On recopie le message dans le buffer
    while (Serial.available() > 0 && i<MAX_WORD_LEN-1 && wordCount < MAX_WORDS_NB){
        c = Serial.read();
        if (c == ' '){
            mots[wordCount][j] = '\0';
            wordCount ++;
            j = 0;
        } else {
            mots[wordCount][j] = c;
            j++;
        }
        i++;
    }
    mots[wordCount][j] = '\0';

    for (int i = 0; i<commandes.len; i++){
        if (compare_code(mots[0], commandes.table[i])){
            msg.code = i;
            msg.timeout = atoi(mots[1]);
            msg.voltage = atoi(mots[2]);
        }
    }

    Serial.println(msg.code);
    Serial.println(msg.timeout);
    Serial.println(msg.voltage);
    return msg;
}

bool compare_code(const char* str1, const char* str2){
    int16_t i = 0;
    while (i<24){
        if (str1[i] != str2[i]){
            return false;
        }
        if (str1[i] == '\0'){
            return true;
        }
        i++;
    }
    return true;
}