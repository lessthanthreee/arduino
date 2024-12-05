#include <Servo.h>

// Pin definitions for motors (exactly as in working test)
#define ENA 10  // Right motor speed
#define IN1 9   // Right motor direction
#define IN2 8   // Right motor direction
#define ENB 5   // Left motor speed
#define IN3 7   // Left motor direction
#define IN4 6   // Left motor direction

// Additional pins for sensors
#define SERVO_PIN 13
#define TRIG_PIN 12
#define ECHO_PIN 11

// Constants
const int OBSTACLE_DISTANCE = 20;  // cm
const int TURN_TIME = 750;        // ms

Servo myservo;

void setup() {
  // Set all motor pins as outputs (exactly as in working test)
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Initialize servo
  myservo.attach(SERVO_PIN);
  myservo.write(90);
  
  // Initialize ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
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
  // Check distance
  int distance = getDistance();
  
  if (distance < OBSTACLE_DISTANCE) {
    // Stop both motors (exactly as in working test)
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    
    delay(1000);  // Wait 1 second
    
    // Turn right
    analogWrite(ENA, 200);  // Right motor speed
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH); // Right motor backward
    
    analogWrite(ENB, 200);  // Left motor speed
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH); // Left motor forward
    
    delay(TURN_TIME);
  } else {
    // Move both motors forward (exactly as in working test)
    analogWrite(ENA, 200);  // Right motor speed
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW); // Right motor forward

    analogWrite(ENB, 200);  // Left motor speed
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH); // Left motor forward
  }
  
  delay(50);  // Small delay between readings
}
