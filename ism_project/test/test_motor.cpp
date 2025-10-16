#include <Arduino.h>
#include "motor.h"

cfg_motor M1 = {34, 35, 12};
cfg_motor M2 = {37, 36, 8};

void test_motor_init() {
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

void test_motor_loop() {
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