#include <Arduino.h>

// Right Motor Pins
#define ENA 5   // Right motor speed
#define IN1 7   // Right motor direction 1
#define IN2 6   // Right motor direction 2

// Left Motor Pins
#define ENB 10  // Left motor speed
#define IN3 9   // Left motor direction 1
#define IN4 8   // Left motor direction 2

const int MOTOR_SPEED = 200;

void setup() {
  Serial.begin(9600);
  
  // Motor Pin Setup
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.println("MOTOR DIRECTION VERIFICATION");
  Serial.println("Observe wheel rotation carefully");
}

void testRightMotorConfiguration1() {
  Serial.println("\n--- RIGHT MOTOR CONFIG 1 ---");
  Serial.println("IN1 HIGH, IN2 LOW");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, MOTOR_SPEED);
  
  Serial.println("Wheel should move FORWARD");
  delay(2000);
  
  // Stop motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

void testRightMotorConfiguration2() {
  Serial.println("\n--- RIGHT MOTOR CONFIG 2 ---");
  Serial.println("IN1 LOW, IN2 HIGH");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, MOTOR_SPEED);
  
  Serial.println("Wheel should move BACKWARD");
  delay(2000);
  
  // Stop motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

void testLeftMotorConfiguration1() {
  Serial.println("\n--- LEFT MOTOR CONFIG 1 ---");
  Serial.println("IN3 HIGH, IN4 LOW");
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, MOTOR_SPEED);
  
  Serial.println("Wheel should move FORWARD");
  delay(2000);
  
  // Stop motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void testLeftMotorConfiguration2() {
  Serial.println("\n--- LEFT MOTOR CONFIG 2 ---");
  Serial.println("IN3 LOW, IN4 HIGH");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, MOTOR_SPEED);
  
  Serial.println("Wheel should move BACKWARD");
  delay(2000);
  
  // Stop motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void loop() {
  // Test right motor configurations
  testRightMotorConfiguration1();
  delay(1000);
  testRightMotorConfiguration2();
  delay(1000);
  
  // Test left motor configurations
  testLeftMotorConfiguration1();
  delay(1000);
  testLeftMotorConfiguration2();
  delay(1000);
}
