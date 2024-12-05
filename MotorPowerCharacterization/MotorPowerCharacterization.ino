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
  
  Serial.println("MOTOR POWER CHARACTERIZATION TEST");
  Serial.println("Speed | Movement | Notes");
  Serial.println("------|----------|------");
}

void testMotorAtSpeed(int speed) {
  // Reset motor state
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  delay(50);
  
  // Set motor direction
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  // Apply speed
  analogWrite(ENB, speed);
  
  // Observe and log
  Serial.print(speed);
  Serial.print("   | ");
  
  // Give motor time to move
  delay(1000);
  
  // Check if motor moves
  if (speed > 100) {
    Serial.print("STRONG  | ");
    Serial.println("Definite Movement");
  } else if (speed > 70) {
    Serial.print("WEAK    | ");
    Serial.println("Minimal/Inconsistent Movement");
  } else {
    Serial.print("NONE    | ");
    Serial.println("No Detectable Movement");
  }
  
  // Stop motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  
  delay(1000);
}

void testWithSensors(int speed) {
  Serial.println("\n--- SENSORS ACTIVE TEST ---");
  
  // Motor at specified speed
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
  
  // Servo sweep
  int sweepAngles[] = {0, 90, 180};
  for (int i = 0; i < 3; i++) {
    servo_motor.write(sweepAngles[i]);
    delay(500);
    
    // Ping distance
    int distance = sonar.ping_cm();
    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.print(" | Angle: ");
    Serial.print(sweepAngles[i]);
    Serial.print(" | Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  
  // Stop motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  
  delay(1000);
}

void loop() {
  // Power Characterization
  int speeds[] = {30, 50, 70, 90, 110, 130, 150, 180, 200, 255};
  
  Serial.println("\n=== MOTOR POWER BASELINE ===");
  for (int i = 0; i < 10; i++) {
    testMotorAtSpeed(speeds[i]);
  }
  
  // Sensor Interaction Test
  Serial.println("\n=== SENSOR INTERACTION TEST ===");
  int sensorTestSpeeds[] = {70, 130, 255};
  for (int i = 0; i < 3; i++) {
    testWithSensors(sensorTestSpeeds[i]);
  }
  
  // Prevent repeated tests
  while(1) {
    delay(10000);
  }
}
