#include <Arduino.h>

// Left Motor Pins
#define LEFT_ENB 10  // Left motor speed
#define LEFT_IN3 9   // Left motor direction
#define LEFT_IN4 8   // Left motor direction

// Right Motor Pins
#define RIGHT_ENA 5  // Right motor speed
#define RIGHT_IN1 7  // Right motor direction
#define RIGHT_IN2 6  // Right motor direction

void setupMotorPins() {
  // Left Motor Pins
  pinMode(LEFT_ENB, OUTPUT);
  pinMode(LEFT_IN3, OUTPUT);
  pinMode(LEFT_IN4, OUTPUT);
  
  // Right Motor Pins
  pinMode(RIGHT_ENA, OUTPUT);
  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);
}

void runMotorsSideBySide(int leftSpeed, int rightSpeed, bool forward = true) {
  Serial.print("LEFT Speed: ");
  Serial.print(leftSpeed);
  Serial.print(" | RIGHT Speed: ");
  Serial.println(rightSpeed);
  
  // Reset motor states
  digitalWrite(LEFT_IN3, LOW);
  digitalWrite(LEFT_IN4, LOW);
  digitalWrite(RIGHT_IN1, LOW);
  digitalWrite(RIGHT_IN2, LOW);
  
  analogWrite(LEFT_ENB, 0);
  analogWrite(RIGHT_ENA, 0);
  
  delay(50);
  
  // Set motor directions
  if (forward) {
    digitalWrite(LEFT_IN3, HIGH);
    digitalWrite(LEFT_IN4, LOW);
    digitalWrite(RIGHT_IN1, HIGH);
    digitalWrite(RIGHT_IN2, LOW);
  } else {
    digitalWrite(LEFT_IN3, LOW);
    digitalWrite(LEFT_IN4, HIGH);
    digitalWrite(RIGHT_IN1, LOW);
    digitalWrite(RIGHT_IN2, HIGH);
  }
  
  // Apply speeds
  analogWrite(LEFT_ENB, leftSpeed);
  analogWrite(RIGHT_ENA, rightSpeed);
  
  // Run for duration
  delay(1000);
  
  // Stop motors
  digitalWrite(LEFT_IN3, LOW);
  digitalWrite(LEFT_IN4, LOW);
  digitalWrite(RIGHT_IN1, LOW);
  digitalWrite(RIGHT_IN2, LOW);
  
  analogWrite(LEFT_ENB, 0);
  analogWrite(RIGHT_ENA, 0);
  
  delay(500);
}

void setup() {
  Serial.begin(9600);
  setupMotorPins();
  
  Serial.println("SIMULTANEOUS MOTOR PERFORMANCE TEST");
  delay(2000);
}

void loop() {
  // Test scenarios
  Serial.println("\n--- FORWARD MOVEMENT TESTS ---");
  runMotorsSideBySide(70, 70);    // Low speed both
  runMotorsSideBySide(100, 100);  // Medium speed both
  runMotorsSideBySide(200, 200);  // High speed both
  runMotorsSideBySide(255, 255);  // Max speed both
  
  Serial.println("\n--- ASYMMETRIC SPEED TESTS ---");
  runMotorsSideBySide(70, 255);   // Left low, Right high
  runMotorsSideBySide(255, 70);   // Left high, Right low
  
  Serial.println("\n--- REVERSE MOVEMENT TESTS ---");
  runMotorsSideBySide(70, 70, false);    // Low speed reverse
  runMotorsSideBySide(255, 255, false);  // Max speed reverse
  
  // Prevent repeated tests
  while(1) {
    delay(10000);
  }
}
