#include <Servo.h>

// Left motor pins (corrected)
#define ENA 10  // Left motor speed
#define IN1 9   // Left motor direction
#define IN2 8   // Left motor direction

// Sensor pins
#define TRIG_PIN 12
#define ECHO_PIN 11

// Constants
const int OBSTACLE_DISTANCE = 20;  // cm
const int MOTOR_SPEED = 200;      // 0-255

void setup() {
  // Initialize left motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
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
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    
    delay(1000);  // Wait 1 second
  } else {
    // Move left motor forward
    analogWrite(ENA, MOTOR_SPEED);  // Set speed first
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  
  delay(50);  // Small delay between readings
}
