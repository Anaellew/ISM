#include <Arduino.h>

#define PWM_B1  12
#define BI1_1   34
#define BI2_1   35

#define PWM_B2  8
#define BI1_2   37
#define BI2_2   36

#define MAX_DUTY 191
#define MAX_VOLTAGE 9.0

void motor_coast(int motor_id) {
  int pwm, in1, in2;
  if (motor_id == 1) {
    pwm = PWM_B1; in1 = BI1_1; in2 = BI2_1;
  } else {
    pwm = PWM_B2; in1 = BI1_2; in2 = BI2_2;
  }
  analogWrite(pwm, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void motor(float voltage, int motor_id) {
  int pwm, in1, in2;
  if (motor_id == 1) {
    pwm = PWM_B1; in1 = BI1_1; in2 = BI2_1;
  } else {
    pwm = PWM_B2; in1 = BI1_2; in2 = BI2_2;
    voltage = -voltage; // inversion de la tension pour le moteur 2
  }

  if (voltage > MAX_VOLTAGE) voltage = MAX_VOLTAGE;
  if (voltage < -MAX_VOLTAGE) voltage = -MAX_VOLTAGE;

  if (abs(voltage) < 0.05) {
    motor_coast(motor_id);
    return;
  }

  int duty = (int)(abs(voltage) / MAX_VOLTAGE * MAX_DUTY);

  if (voltage > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  analogWrite(pwm, duty);
}

void setup() {
  Serial.begin(115200);
  pinMode(PWM_B1, OUTPUT);
  pinMode(BI1_1, OUTPUT);
  pinMode(BI2_1, OUTPUT);
  pinMode(PWM_B2, OUTPUT);
  pinMode(BI1_2, OUTPUT);
  pinMode(BI2_2, OUTPUT);
  motor_coast(1);
  motor_coast(2);
  Serial.println("Test double moteur prêt !");
}

void loop() {
  Serial.println("➡️  Avance");
  motor(3.0, 1);
  motor(3.0, 2);
  delay(2000);

  Serial.println("⬅️  Recule");
  motor(-3.0, 1);
  motor(-3.0, 2);
  delay(2000);

  Serial.println("↩️  Rotation sur place");
  motor(3.0, 1);
  motor(-3.0, 2);
  delay(2000);

  Serial.println("↪️  Rotation inverse");
  motor(-3.0, 1);
  motor(3.0, 2);
  delay(2000);

  Serial.println("🛑 Roue libre");
  motor(0.0, 1);
  motor(0.0, 2);
  delay(2000);
}
