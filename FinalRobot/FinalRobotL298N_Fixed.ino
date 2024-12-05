#include <Servo.h>
#include <NewPing.h>

// L298N motor control pins - CORRECTED for your setup
#define ENA 10  // Right motor speed (working)
#define IN3 9   // Right motor direction (working)
#define IN4 8   // Right motor direction (working)
#define ENB 5   // Left motor speed
#define IN1 7   // Left motor direction
#define IN2 6   // Left motor direction

// Motor speed
const int MOTOR_SPEED = 200;  // Adjust between 0-255

//sensor pins
#define TRIG_PIN 12
#define ECHO_PIN 11
#define SERVO_PIN 13

#define MAXIMUM_DISTANCE 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAXIMUM_DISTANCE);
Servo servo_motor;

void setup() {
  // Initialize motor control pins
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  servo_motor.attach(SERVO_PIN);
  servo_motor.write(90);
  
  Serial.begin(9600);
  
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20) {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft) {
      turnRight();
      moveStop();
    }
    else {
      turnLeft();
      moveStop();
    }
  }
  else {
    moveForward();
  }
  distance = readPing();
}

int lookRight() {
  servo_motor.write(10);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft() {
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;
    
    // Right motor forward (using IN3/IN4 - the working side)
    analogWrite(ENA, MOTOR_SPEED);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
    // Left motor forward
    analogWrite(ENB, MOTOR_SPEED);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
}

void moveBackward() {
  goesForward = false;
  
  // Right motor backward (using IN3/IN4 - the working side)
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  // Left motor backward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void turnRight() {
  // Right motor backward (using IN3/IN4 - the working side)
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  // Left motor forward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  delay(500);
  
  moveForward();
}

void turnLeft() {
  // Right motor forward (using IN3/IN4 - the working side)
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  // Left motor backward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  delay(500);
  
  moveForward();
}
