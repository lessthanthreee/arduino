#include <Servo.h>

// Motor pins - VERIFIED WORKING
#define ENA 10  // Right motor speed
#define IN3 9   // Right motor direction
#define IN4 8   // Right motor direction
#define ENB 5   // Left motor speed
#define IN1 7   // Left motor direction
#define IN2 6   // Left motor direction

// New sensor pin assignments
#define SERVO_PIN 3  // PWM pin for servo
#define TRIG_PIN 2   // Trigger for ultrasonic
#define ECHO_PIN 4   // Echo for ultrasonic

const int MOTOR_SPEED = 200;
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
  
  Serial.begin(9600);
  
  // Initialize servo with delay
  delay(1000);
  servo_motor.attach(SERVO_PIN);
  servo_motor.write(90);  // Center position
  delay(1000);
  
  Serial.println("Setup complete - starting test");
}

void loop() {
  // Test 1: Servo Movement
  Serial.println("Testing servo...");
  servo_motor.write(0);    // Right
  delay(1000);
  servo_motor.write(90);   // Center
  delay(1000);
  servo_motor.write(180);  // Left
  delay(1000);
  servo_motor.write(90);   // Center
  delay(1000);
  
  // Test 2: Distance Reading
  Serial.println("Testing ultrasonic...");
  int distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(1000);
  
  // Test 3: Motors with Servo centered
  Serial.println("Testing motors...");
  moveForward();
  delay(2000);
  stopMotors();
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
