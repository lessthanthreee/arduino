#include <Servo.h>

// Motor pins - EXACTLY as in working test
#define ENA 10  // Right motor speed
#define IN3 9   // Right motor direction
#define IN4 8   // Right motor direction
#define ENB 5   // Left motor speed
#define IN1 7   // Left motor direction
#define IN2 6   // Left motor direction

// Sensor pins - moved to new locations
#define SERVO_PIN 3
#define TRIG_PIN 2
#define ECHO_PIN 4

const int MOTOR_SPEED = 200;
const int OBSTACLE_DISTANCE = 20;

Servo servo_motor;

void setup() {
  // Initialize motor control pins
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Initialize sensors
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  delay(1000);
  servo_motor.attach(SERVO_PIN);
  servo_motor.write(90);
  
  Serial.begin(9600);
  delay(2000);
}

// USING EXACT SAME MOTOR CONTROL AS WORKING TEST
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
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if (distance < OBSTACLE_DISTANCE) {
    Serial.println("Obstacle detected!");
    
    // Stop
    stopMotors();
    delay(500);
    
    // Look right
    servo_motor.write(0);
    delay(1000);
    
    // Look center
    servo_motor.write(90);
    delay(500);
    
    // Turn right
    turnRight();
    delay(750);
    stopMotors();
    delay(200);
  } else {
    moveForward();
  }
  
  delay(100);
}
