#include <Arduino.h>
#include "motor.h"

#define MAX_DUTY 191
#define MAX_VOLTAGE 9.0

cfg_motor M1 = {34, 35, 12};
cfg_motor M2 = {37, 36, 8};

void motor_coast(cfg_motor M) {
  analogWrite(M.PWM, 0);
  digitalWrite(M.BI1, LOW);
  digitalWrite(M.BI2, LOW);
}

bool control_motor(cfg_motor M, int16_t voltage) {
  if (M.PWM == 0 || M.BI1 == 0 || M.BI2 == 0) return false;

  float v = (float)voltage;
  if (M.BI1 == M2.BI1 && M.BI2 == M2.BI2 && M.PWM == M2.PWM) v = -v; // inversion du sens pour le moteur 2

  if (v > MAX_VOLTAGE) v = MAX_VOLTAGE;
  if (v < -MAX_VOLTAGE) v = -MAX_VOLTAGE;

  if (abs(v) < 0.05) {
    motor_coast(M);
    return true;
  }

  int duty = (int)(abs(v) / MAX_VOLTAGE * MAX_DUTY);

  if (v > 0) {
    digitalWrite(M.BI1, HIGH);
    digitalWrite(M.BI2, LOW);
  } else {
    digitalWrite(M.BI1, LOW);
    digitalWrite(M.BI2, HIGH);
  }

  analogWrite(M.PWM, duty);
  return true;
}
