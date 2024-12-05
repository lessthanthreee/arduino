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

const int MAXIMUM_DISTANCE = 200;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAXIMUM_DISTANCE);
Servo servo_motor;

void setup() {
  Serial.begin(9600);
  
  // Motor Pin Setup
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Servo Setup
  servo_motor.attach(SERVO_PIN);
  servo_motor.write(90);  // Center position
  
  Serial.println("MOTOR THRESHOLD MAPPING TEST");
  Serial.println("Speed | No Load | With Servo | With Sensor");
}

void testMotorThreshold(int speed) {
  // Reset motor state
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  delay(50);
  
  // Set motor direction
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  // Test 1: No Load
  analogWrite(ENB, speed);
  delay(500);
  bool noLoadMovement = digitalRead(IN3) == HIGH;
  
  // Stop motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  delay(50);
  
  // Test 2: With Servo Sweep
  servo_motor.write(0);  // Sweep servo
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
  delay(500);
  bool servoLoadMovement = digitalRead(IN3) == HIGH;
  servo_motor.write(90);  // Reset servo
  
  // Stop motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  delay(50);
  
  // Test 3: With Sensor Ping
  sonar.ping_cm();  // Trigger sensor
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
  delay(500);
  bool sensorLoadMovement = digitalRead(IN3) == HIGH;
  
  // Stop motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  
  // Log results
  Serial.print(speed);
  Serial.print("   | ");
  Serial.print(noLoadMovement ? "MOVE" : "STOP");
  Serial.print("    | ");
  Serial.print(servoLoadMovement ? "MOVE" : "STOP");
  Serial.print("      | ");
  Serial.println(sensorLoadMovement ? "MOVE" : "STOP");
  
  delay(500);
}

void loop() {
  // Systematic speed test with various loads
  int speeds[] = {
    30, 40, 50, 60, 70, 80, 90, 100, 
    110, 120, 130, 140, 150, 200, 255
  };
  
  Serial.println("Speed | No Load | With Servo | With Sensor");
  Serial.println("------|---------|------------|------------");
  
  for (int i = 0; i < 15; i++) {
    testMotorThreshold(speeds[i]);
  }
  
  // Prevent repeated tests
  while(1) {
    delay(10000);
  }
}
