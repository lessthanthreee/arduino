#include <Arduino.h>

// Left Motor Pins
#define LEFT_ENB 10  // Left motor speed
#define LEFT_IN3 9   // Left motor direction
#define LEFT_IN4 8   // Left motor direction

// Right Motor Pins
#define RIGHT_ENA 5  // Right motor speed
#define RIGHT_IN1 7  // Right motor direction
#define RIGHT_IN2 6  // Right motor direction

void setup() {
  Serial.begin(9600);
  delay(2000);
  
  // Configure all motor pins
  pinMode(LEFT_ENB, OUTPUT);
  pinMode(LEFT_IN3, OUTPUT);
  pinMode(LEFT_IN4, OUTPUT);
  pinMode(RIGHT_ENA, OUTPUT);
  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);
  
  Serial.println("MOTOR CONNECTION DIAGNOSTIC");
  Serial.println("==========================");
}

void pinStateTest() {
  Serial.println("\n--- PIN STATE VERIFICATION ---");
  
  int leftPins[] = {LEFT_ENB, LEFT_IN3, LEFT_IN4};
  int rightPins[] = {RIGHT_ENA, RIGHT_IN1, RIGHT_IN2};
  
  const char* leftPinNames[] = {"ENB", "IN3", "IN4"};
  const char* rightPinNames[] = {"ENA", "IN1", "IN2"};
  
  Serial.println("LEFT MOTOR PINS:");
  for (int i = 0; i < 3; i++) {
    pinMode(leftPins[i], OUTPUT);
    digitalWrite(leftPins[i], HIGH);
    delay(100);
    Serial.print(leftPinNames[i]);
    Serial.print(" (Pin ");
    Serial.print(leftPins[i]);
    Serial.print("): ");
    Serial.println(digitalRead(leftPins[i]));
    digitalWrite(leftPins[i], LOW);
  }
  
  Serial.println("\nRIGHT MOTOR PINS:");
  for (int i = 0; i < 3; i++) {
    pinMode(rightPins[i], OUTPUT);
    digitalWrite(rightPins[i], HIGH);
    delay(100);
    Serial.print(rightPinNames[i]);
    Serial.print(" (Pin ");
    Serial.print(rightPins[i]);
    Serial.print("): ");
    Serial.println(digitalRead(rightPins[i]));
    digitalWrite(rightPins[i], LOW);
  }
}

void continuityTest() {
  Serial.println("\n--- MOTOR CONNECTION CONTINUITY ---");
  
  // Test left motor connections
  Serial.println("LEFT MOTOR CONTINUITY:");
  digitalWrite(LEFT_IN3, HIGH);
  digitalWrite(LEFT_IN4, LOW);
  for (int speed = 0; speed <= 255; speed += 50) {
    analogWrite(LEFT_ENB, speed);
    Serial.print("Speed ");
    Serial.print(speed);
    Serial.println(": Testing...");
    delay(200);
  }
  analogWrite(LEFT_ENB, 0);
  
  // Test right motor connections
  Serial.println("\nRIGHT MOTOR CONTINUITY:");
  digitalWrite(RIGHT_IN1, HIGH);
  digitalWrite(RIGHT_IN2, LOW);
  for (int speed = 0; speed <= 255; speed += 50) {
    analogWrite(RIGHT_ENA, speed);
    Serial.print("Speed ");
    Serial.print(speed);
    Serial.println(": Testing...");
    delay(200);
  }
  analogWrite(RIGHT_ENA, 0);
}

void voltageTest() {
  Serial.println("\n--- VOLTAGE DIAGNOSTIC ---");
  
  // Measure voltage at different motor states
  Serial.println("Checking voltage stability:");
  
  int testSpeeds[] = {70, 150, 255};
  
  for (int speed : testSpeeds) {
    Serial.print("\nTesting at Speed: ");
    Serial.println(speed);
    
    // Left Motor
    digitalWrite(LEFT_IN3, HIGH);
    digitalWrite(LEFT_IN4, LOW);
    analogWrite(LEFT_ENB, speed);
    
    // Right Motor
    digitalWrite(RIGHT_IN1, HIGH);
    digitalWrite(RIGHT_IN2, LOW);
    analogWrite(RIGHT_ENA, speed);
    
    delay(500);
    
    // Stop motors
    analogWrite(LEFT_ENB, 0);
    analogWrite(RIGHT_ENA, 0);
    digitalWrite(LEFT_IN3, LOW);
    digitalWrite(LEFT_IN4, LOW);
    digitalWrite(RIGHT_IN1, LOW);
    digitalWrite(RIGHT_IN2, LOW);
    
    delay(200);
  }
}

void loop() {
  pinStateTest();
  continuityTest();
  voltageTest();
  
  // Prevent repeated tests
  while(1) {
    delay(10000);
  }
}
