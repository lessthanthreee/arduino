#include <Arduino.h>

// Left Motor Pins
#define ENB 10  // Left motor speed
#define IN3 9   // Left motor direction
#define IN4 8   // Left motor direction

void setup() {
  Serial.begin(9600);
  
  // Motor Pin Setup
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.println("MINIMUM MOTOR SPEED TEST");
  Serial.println("Speed | Movement");
  Serial.println("------|----------");
}

void testMotorSpeed(int speed) {
  // Reset motor state
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  delay(50);
  
  // Set motor direction
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  // Apply speed
  analogWrite(ENB, speed);
  
  // Print test details
  Serial.print(speed);
  Serial.print("   | ");
  
  // Give motor time to move
  delay(1000);
  
  // Stop motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  
  // Pause between tests
  delay(1000);
}

void loop() {
  // Systematic speed test
  int speeds[] = {
    30, 40, 50, 60, 70, 80, 90, 100, 
    110, 120, 130, 140, 150, 200, 255
  };
  
  for (int i = 0; i < 15; i++) {
    testMotorSpeed(speeds[i]);
  }
  
  // Prevent repeated tests
  while(1) {
    delay(10000);
  }
}
