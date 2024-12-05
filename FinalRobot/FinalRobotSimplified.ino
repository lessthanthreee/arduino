#include <Servo.h>

// Motor pins - VERIFIED WORKING CONFIG
#define ENA 10  // Right motor speed
#define IN3 9   // Right motor direction
#define IN4 8   // Right motor direction
#define ENB 5   // Left motor speed
#define IN1 7   // Left motor direction
#define IN2 6   // Left motor direction

// Sensor pins - Moved away from motor pins
#define TRIG_PIN 12
#define ECHO_PIN 11
#define SERVO_PIN 13

// Constants
const int MOTOR_SPEED = 200;
const int TURN_TIME = 750;
const int OBSTACLE_DISTANCE = 20;

Servo servo_motor;

void setup() {
  // Motor setup
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Sensor setup
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Servo setup - with delay to avoid interference
  delay(500);
  servo_motor.attach(SERVO_PIN);
  servo_motor.write(90);
  delay(500);
  
  Serial.begin(9600);
  delay(1000);
}

int getDistance() {
  // Clear trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Send trigger pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read echo
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

// VERIFIED WORKING MOVEMENT FUNCTIONS
void moveForward() {
  // Right motor forward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  // Left motor forward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void stopMotors() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void turnRight() {
  // Right motor backward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  // Left motor forward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void checkAndAvoid() {
  int distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if (distance < OBSTACLE_DISTANCE) {
    Serial.println("Obstacle detected!");
    
    // Stop and wait
    stopMotors();
    delay(200);
    
    // Look right
    servo_motor.write(0);
    delay(500);
    int rightDistance = getDistance();
    
    // Look left
    servo_motor.write(180);
    delay(500);
    int leftDistance = getDistance();
    
    // Return to center
    servo_motor.write(90);
    delay(500);
    
    // Choose direction
    if (rightDistance > leftDistance) {
      Serial.println("Turning right");
      turnRight();
      delay(TURN_TIME);
    } else {
      Serial.println("Turning left");
      turnRight();  // For now, always turn right
      delay(TURN_TIME);
    }
    
    stopMotors();
    delay(200);
  }
}

void loop() {
  // Simple main loop
  checkAndAvoid();
  moveForward();
  delay(100);  // Short delay between checks
}
