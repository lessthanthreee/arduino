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

void testMotorMovement(int motorSpeedPin, int motorDir1Pin, int motorDir2Pin, String motorName) {
  Serial.println("\n--- " + motorName + " MOTOR DIAGNOSTIC ---");
  
  int testSpeeds[] = {50, 100, 200, 255};
  
  for (int i = 0; i < 4; i++) {
    Serial.print("Testing Speed: ");
    Serial.println(testSpeeds[i]);
    
    // Reset motor state
    digitalWrite(motorDir1Pin, LOW);
    digitalWrite(motorDir2Pin, LOW);
    analogWrite(motorSpeedPin, 0);
    delay(50);
    
    // Forward Direction
    digitalWrite(motorDir1Pin, HIGH);
    digitalWrite(motorDir2Pin, LOW);
    analogWrite(motorSpeedPin, testSpeeds[i]);
    
    Serial.println("Forward Direction");
    delay(1000);
    
    // Reverse Direction
    digitalWrite(motorDir1Pin, LOW);
    digitalWrite(motorDir2Pin, HIGH);
    analogWrite(motorSpeedPin, testSpeeds[i]);
    
    Serial.println("Reverse Direction");
    delay(1000);
    
    // Stop motor
    digitalWrite(motorDir1Pin, LOW);
    digitalWrite(motorDir2Pin, LOW);
    analogWrite(motorSpeedPin, 0);
    
    delay(500);
  }
}

void setup() {
  Serial.begin(9600);
  setupMotorPins();
  
  Serial.println("COMPREHENSIVE MOTOR HEALTH CHECK");
  delay(2000);
}

void loop() {
  // Test Left Motor
  testMotorMovement(LEFT_ENB, LEFT_IN3, LEFT_IN4, "LEFT");
  
  // Test Right Motor for comparison
  testMotorMovement(RIGHT_ENA, RIGHT_IN1, RIGHT_IN2, "RIGHT");
  
  // Prevent repeated tests
  while(1) {
    delay(10000);
  }
}
