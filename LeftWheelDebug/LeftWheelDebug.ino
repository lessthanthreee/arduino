#include <Servo.h>
#include <NewPing.h>

// Comprehensive Debug Sketch

// Motor pins
#define ENB 10  // Left motor speed
#define IN3 9   // Left motor direction
#define IN4 8   // Left motor direction

// Sensor pins
#define SERVO_PIN 3    // Servo on pin 3
#define TRIG_PIN 2     // Ultrasonic TRIG on pin 2
#define ECHO_PIN 4     // Ultrasonic ECHO on pin 4

const int MOTOR_SPEED = 200;
const int OBSTACLE_DISTANCE = 15;  // cm
const int MAXIMUM_DISTANCE = 200;  // cm

NewPing sonar(TRIG_PIN, ECHO_PIN, MAXIMUM_DISTANCE);
Servo servo_motor;

void setup() {
  Serial.begin(9600);
  delay(2000);
  
  // VERBOSE Motor Pin Setup
  Serial.println("Motor Pin Setup:");
  pinMode(ENB, OUTPUT);
  Serial.print("ENB (speed pin) set as OUTPUT: "); Serial.println(ENB);
  
  pinMode(IN3, OUTPUT);
  Serial.print("IN3 (direction pin) set as OUTPUT: "); Serial.println(IN3);
  
  pinMode(IN4, OUTPUT);
  Serial.print("IN4 (direction pin) set as OUTPUT: "); Serial.println(IN4);
  
  // VERBOSE Servo Setup
  Serial.println("\nServo Setup:");
  servo_motor.attach(SERVO_PIN);
  Serial.print("Servo attached to pin: "); Serial.println(SERVO_PIN);
  servo_motor.write(90);  // Center position
  Serial.println("Servo centered at 90 degrees");
  
  // VERBOSE Sensor Setup
  Serial.println("\nUltrasonic Sensor Setup:");
  Serial.print("TRIG PIN: "); Serial.println(TRIG_PIN);
  Serial.print("ECHO PIN: "); Serial.println(ECHO_PIN);
}

void testMotorMovement() {
  Serial.println("\n--- MOTOR MOVEMENT TEST ---");
  
  // Test Forward
  Serial.println("Testing Forward Movement");
  Serial.print("ENB Speed: "); Serial.println(MOTOR_SPEED);
  Serial.println("IN3: HIGH, IN4: LOW");
  
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  delay(2000);  // Move for 2 seconds
  
  // Stop
  Serial.println("STOPPING MOTOR");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  
  delay(1000);
  
  // Test Backward
  Serial.println("Testing Backward Movement");
  Serial.println("IN3: LOW, IN4: HIGH");
  
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  delay(2000);  // Move for 2 seconds
  
  // Stop
  Serial.println("STOPPING MOTOR");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void testServoAndSensor() {
  Serial.println("\n--- SERVO AND SENSOR TEST ---");
  
  // Test Servo Sweep
  Serial.println("Servo Sweep Test");
  servo_motor.write(0);   // Right
  delay(1000);
  
  servo_motor.write(90);  // Center
  delay(1000);
  
  servo_motor.write(180); // Left
  delay(1000);
  
  servo_motor.write(90);  // Back to center
  
  // Test Distance Measurement
  Serial.println("Distance Measurement");
  int distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void loop() {
  // Alternate between motor and sensor tests
  static bool motorTest = true;
  
  if (motorTest) {
    testMotorMovement();
  } else {
    testServoAndSensor();
  }
  
  motorTest = !motorTest;
  
  delay(2000);  // Pause between tests
}
