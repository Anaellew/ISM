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

void init2() {
  Serial.begin(115200);

  pinMode(M1.PWM, OUTPUT);
  pinMode(M1.BI1, OUTPUT);
  pinMode(M1.BI2, OUTPUT);

  pinMode(M2.PWM, OUTPUT);
  pinMode(M2.BI1, OUTPUT);
  pinMode(M2.BI2, OUTPUT);

  motor_coast(M1);
  motor_coast(M2);

  Serial.println("Test moteurs structuré prêt !");
}

void test() {
  Serial.println("➡️  Avance des deux moteurs (+3 V)...");
  control_motor(M1, 3);
  control_motor(M2, 3);
  delay(2000);

  Serial.println("⬅️  Recul des deux moteurs (-3 V)...");
  control_motor(M1, -3);
  control_motor(M2, -3);
  delay(2000);

  Serial.println("↩️  Rotation sur place : M1 avance, M2 recule");
  control_motor(M1, 3);
  control_motor(M2, -3);
  delay(2000);

  Serial.println("↪️  Rotation inverse : M1 recule, M2 avance");
  control_motor(M1, -3);
  control_motor(M2, 3);
  delay(2000);

  Serial.println("🛑 Roue libre...");
  control_motor(M1, 0);
  control_motor(M2, 0);
  delay(2000);
}