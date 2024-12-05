#include <Servo.h>

// Left motor pins only
#define ENB 5   // Left motor speed
#define IN3 7   // Left motor direction
#define IN4 6   // Left motor direction

// Sensor pins
#define TRIG_PIN 12
#define ECHO_PIN 11

// Constants
const int OBSTACLE_DISTANCE = 20;  // cm
const int MOTOR_SPEED = 200;      // 0-255

void setup() {
  // Initialize left motor pins
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Initialize ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Optional: Serial for debugging
  Serial.begin(9600);
  
  delay(2000);  // Initial delay
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void loop() {
  // Get distance
  int distance = getDistance();
  
  // Print distance (optional)
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if (distance < OBSTACLE_DISTANCE) {
    // Stop if obstacle detected
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
    
    delay(1000);  // Wait 1 second
  } else {
    // Move left motor forward
    analogWrite(ENB, MOTOR_SPEED);  // Set speed first
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  
  delay(50);  // Small delay between readings
}
