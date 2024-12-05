#include <Servo.h>

// Pin definitions
#define SERVO_PIN 13
#define TRIG_PIN 12
#define ECHO_PIN 11
#define ENA 10
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define ENB 5

// Constants
const int OBSTACLE_DISTANCE = 20;  // cm
const int MOTOR_SPEED = 200;      // 0-255
const int TURN_TIME = 750;        // ms

Servo myservo;
int servoPos = 90;  // Center position

void setup() {
  // Initialize servo
  myservo.attach(SERVO_PIN);
  myservo.write(90);  // Center position
  
  // Initialize ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize motor pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Initial 2-second delay to position robot
  delay(2000);
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

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void turnRightMotors() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void scanArea() {
  // Scan right
  for(int i = 90; i <= 180; i += 10) {
    myservo.write(i);
    delay(100);
    if(getDistance() > OBSTACLE_DISTANCE) {
      return; // Found clear path
    }
  }
  
  // Scan left
  for(int i = 180; i >= 0; i -= 10) {
    myservo.write(i);
    delay(100);
    if(getDistance() > OBSTACLE_DISTANCE) {
      return; // Found clear path
    }
  }
  
  // Return to center
  myservo.write(90);
}

void loop() {
  // Check forward distance
  myservo.write(90);
  delay(100);
  int distance = getDistance();
  
  if (distance < OBSTACLE_DISTANCE) {
    // Obstacle detected
    stopMotors();
    delay(200);
    
    // Scan area for clear path
    scanArea();
    
    // Turn right and continue
    turnRightMotors();
    delay(TURN_TIME);
    stopMotors();
    delay(200);
  } else {
    // No obstacle, move forward - using exact code from working test
    analogWrite(ENA, MOTOR_SPEED);  // Right motor speed
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW); // Right motor forward

    analogWrite(ENB, MOTOR_SPEED);  // Left motor speed
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH); // Left motor forward
  }
  
  delay(50);  // Small delay between readings
}
