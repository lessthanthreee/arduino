#include <Servo.h>

// Motor pins - KEEP THESE THE SAME (working configuration)
#define ENA 10  // Right motor speed
#define IN3 9   // Right motor direction
#define IN4 8   // Right motor direction
#define ENB 5   // Left motor speed
#define IN1 7   // Left motor direction
#define IN2 6   // Left motor direction

// NEW PIN ASSIGNMENTS for sensors
#define SERVO_PIN 4     // Moved servo to pin 4
#define TRIG_PIN 3      // Moved trigger to pin 3
#define ECHO_PIN 2      // Moved echo to pin 2

const int MOTOR_SPEED = 200;

Servo servo_motor;

void setup() {
  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.begin(9600);
  
  // Initialize servo with delays
  delay(1000);
  servo_motor.attach(SERVO_PIN);
  delay(500);
  
  Serial.println("Starting test sequence...");
}

void loop() {
  // Test sequence
  Serial.println("Moving forward...");
  moveForward();
  delay(2000);
  
  Serial.println("Stopping...");
  stopMotors();
  delay(1000);
  
  Serial.println("Scanning right...");
  servo_motor.write(0);
  delay(1000);
  
  Serial.println("Scanning center...");
  servo_motor.write(90);
  delay(1000);
  
  Serial.println("Scanning left...");
  servo_motor.write(180);
  delay(1000);
  
  Serial.println("Back to center...");
  servo_motor.write(90);
  delay(1000);
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
