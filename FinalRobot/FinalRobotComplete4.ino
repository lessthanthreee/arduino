#include <Servo.h>
#include <NewPing.h>

// Motor Driver Pins
#define ENA 5   // Right motor speed
#define IN1 7   // Right motor direction
#define IN2 6   // Right motor direction
#define ENB 10  // Left motor speed
#define IN3 9   // Left motor direction
#define IN4 8   // Left motor direction

// Sensor Pins
#define SERVO_PIN 3
#define TRIG_PIN 2
#define ECHO_PIN 4

// Constants
#define MAXIMUM_DISTANCE 200
#define FULL_SPEED 255
#define TURN_SPEED 200

// Sensor Objects
NewPing sonar(TRIG_PIN, ECHO_PIN, MAXIMUM_DISTANCE);
Servo servo_motor;

// Global Variables
int distance = 0;
int leftSpeed = FULL_SPEED;   // Always use full speed for left motor
int rightSpeed = FULL_SPEED;

void setup() {
  Serial.begin(9600);
  
  // Motor Pin Setup
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Servo Setup
  servo_motor.attach(SERVO_PIN);
  servo_motor.write(90);  // Center position
  
  Serial.println("Obstacle Avoiding Robot Initialized");
}

void moveForward() {
  // Right Motor Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, rightSpeed);
  
  // Left Motor Forward (Always Full Speed)
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, leftSpeed);
  
  Serial.println("Moving Forward");
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  
  Serial.println("Motors Stopped");
}

void turnRight() {
  // Right Motor Backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, TURN_SPEED);
  
  // Left Motor Forward (Always Full Speed)
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, leftSpeed);
  
  Serial.println("Turning Right");
}

void turnLeft() {
  // Right Motor Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, TURN_SPEED);
  
  // Left Motor Backward (Always Full Speed)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, leftSpeed);
  
  Serial.println("Turning Left");
}

int getDistance() {
  servo_motor.write(90);  // Center servo
  delay(100);
  return sonar.ping_cm();
}

void loop() {
  distance = getDistance();
  
  if (distance > 25 || distance == 0) {
    // Path is clear, move forward
    moveForward();
    delay(100);
  } else {
    // Obstacle detected, stop and decide
    stopMotors();
    delay(500);
    
    // Look right
    servo_motor.write(0);
    delay(500);
    int rightDistance = sonar.ping_cm();
    
    // Look left
    servo_motor.write(180);
    delay(500);
    int leftDistance = sonar.ping_cm();
    
    // Decide turn direction
    if (rightDistance > leftDistance) {
      turnRight();
      delay(500);
    } else {
      turnLeft();
      delay(500);
    }
  }
}
