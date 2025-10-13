#include <Arduino.h>
#include <communication.h>

message_t receive(){
    message_t msg;
    char mots[24][3] = {0};
    char c;
    int16_t i = 0;
    int16_t j = 0;
    int16_t wordCount = 0;

    // On recopie le message dans le buffer
    while (Serial.available() > 0 && i<24 && wordCount < 3){
        c = Serial.read();
        if (c == ' '){
            wordCount ++;
            mots[j][wordCount] = '\0';
            j = 0;
        } else {
            mots[j][wordCount] = c;
            j++;
        }
        i++;
    }
    mots[j][wordCount] = '\0';

    if (compare_code(mots[0], "STOP")){
        msg.code = code_stop;
        msg.timeout = 0;
        msg.voltage = 0;
    } else if (compare_code(mots[0], "FORWARD")){
        msg.code = code_forward;
        msg.timeout = atoi(mots[1]);
        msg.voltage = atoi(mots[2]);
    } else if (compare_code(mots[0], "TURN")){
        msg.code = code_turn;
        msg.timeout = atoi(mots[1]);
        msg.voltage = atoi(mots[2]);
    }
    return msg;
}

bool send(message_t msg){
    // A implémenter en temps voulu
    return false;
}

bool compare_code(char str1[24], char str2[24]){
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