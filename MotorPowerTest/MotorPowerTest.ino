#include <Servo.h>
#include <NewPing.h>

// Left Motor Pins
#define ENB 10  // Left motor speed
#define IN3 9   // Left motor direction
#define IN4 8   // Left motor direction

// Sensor Pins
#define SERVO_PIN 3
#define TRIG_PIN 2
#define ECHO_PIN 4

const int MOTOR_SPEED = 200;
const int MAXIMUM_DISTANCE = 200;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAXIMUM_DISTANCE);
Servo servo_motor;

void setup() {
  Serial.begin(9600);
  delay(2000);
  
  // Motor Pin Setup
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Sensor Setup
  servo_motor.attach(SERVO_PIN);
  servo_motor.write(90);  // Center position
  
  Serial.println("MOTOR POWER AND INTERFERENCE TEST");
}

void measureMotorCurrent(int speed) {
  Serial.println("\n--- MOTOR CURRENT MEASUREMENT ---");
  Serial.print("Motor Speed: "); Serial.println(speed);
  
  // Measure motor behavior with different loads
  Serial.println("1. Motor Alone");
  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(1000);
  
  Serial.println("2. Motor with Servo Sweeping");
  servo_motor.write(0);   // Right
  delay(500);
  servo_motor.write(180); // Left
  delay(500);
  servo_motor.write(90);  // Center
  
  Serial.println("3. Motor with Sensor Pinging");
  int distance = sonar.ping_cm();
  Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");
  
  Serial.println("4. Motor with Servo and Sensor");
  servo_motor.write(0);   // Right
  distance = sonar.ping_cm();
  servo_motor.write(180); // Left
  distance = sonar.ping_cm();
  servo_motor.write(90);  // Center
  
  // Stop motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  
  delay(1000);
}

void loop() {
  // Test at different speeds
  measureMotorCurrent(100);   // Low speed
  measureMotorCurrent(200);   // Medium speed
  measureMotorCurrent(255);   // Full speed
  
  delay(2000);
}
