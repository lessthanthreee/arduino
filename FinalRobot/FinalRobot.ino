#include <Servo.h>
#include <NewPing.h>

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
#define RIGHT_LINE_SENSOR A0
#define LEFT_LINE_SENSOR A1
#define RIGHT_LINE_SENSOR_D0 2
#define LEFT_LINE_SENSOR_D0 3

// Constants
const int OBSTACLE_DISTANCE = 20;  // cm
const int MOTOR_SPEED = 200;      // 0-255
const int TURN_TIME = 750;        // ms
const int MAX_DISTANCE = 200;     // Maximum distance to ping for (in cm)

Servo myservo;
int servoPos = 90;  // Center position

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  // Initialize servo
  myservo.attach(SERVO_PIN);
  myservo.write(90);  // Center position
  
  // Initialize motor pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Initialize line sensor pins
  pinMode(RIGHT_LINE_SENSOR_D0, INPUT);
  pinMode(LEFT_LINE_SENSOR_D0, INPUT);
  
  // Initial 2-second delay to position robot
  delay(2000);
}

int getDistance() {
  return sonar.ping_cm();
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
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
  // Read line sensors
  int rightLineDetected = digitalRead(RIGHT_LINE_SENSOR_D0);
  int leftLineDetected = digitalRead(LEFT_LINE_SENSOR_D0);
  
  if (rightLineDetected == LOW || leftLineDetected == LOW) {
    // Line detected
    if (rightLineDetected == LOW && leftLineDetected == HIGH) {
      // Turn slightly left
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    } else if (leftLineDetected == LOW && rightLineDetected == HIGH) {
      // Turn slightly right
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else {
      // Move forward
      forward();
    }
  } else {
    // No line detected, check for obstacles
    int distance = getDistance();
    if (distance < OBSTACLE_DISTANCE) {
      stop();
      delay(200);
      scanArea();
      turnRight();
      delay(TURN_TIME);
      stop();
      delay(200);
    } else {
      forward();
    }
  }
  delay(50);  // Small delay between readings
}
