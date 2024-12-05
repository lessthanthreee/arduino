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

const int MAX_SPEED = 255;
const int MAXIMUM_DISTANCE = 200;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAXIMUM_DISTANCE);
Servo servo_motor;

void setup() {
  Serial.begin(9600);
  delay(2000);
  
  // EXPLICIT Power Management Setup
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Ensure initial motor stop
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  
  // Servo Setup with Power Management
  servo_motor.attach(SERVO_PIN);
  servo_motor.write(90);  // Center position
  
  Serial.println("ADVANCED POWER MANAGEMENT TEST");
}

void safeMotorControl(int speed) {
  // Disable motor briefly before changing state
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  delay(10);  // Short pause to stabilize
  
  Serial.print("Motor Speed: ");
  Serial.println(speed);
  
  // Controlled motor activation
  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void safeSensorTest() {
  // Controlled sensor activation
  Serial.println("Sensor Activation Sequence");
  
  // Servo sweep with power management
  int angles[] = {0, 90, 180, 90};
  for (int i = 0; i < 4; i++) {
    servo_motor.write(angles[i]);
    delay(500);  // Controlled movement
    
    // Ping between servo movements
    int distance = sonar.ping_cm();
    Serial.print("Angle: ");
    Serial.print(angles[i]);
    Serial.print(" | Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
}

void powerCycleTest() {
  Serial.println("\n--- POWER CYCLE TEST ---");
  
  // Cycle through different power management scenarios
  int speeds[] = {MAX_SPEED, MAX_SPEED/2, MAX_SPEED/4};
  
  for (int j = 0; j < 3; j++) {
    Serial.print("\nTesting Speed: ");
    Serial.println(speeds[j]);
    
    // Motor with brief sensor interaction
    safeMotorControl(speeds[j]);
    delay(500);  // Motor running
    
    safeSensorTest();
    
    // Ensure motor stops cleanly
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
    
    delay(1000);  // Recovery time
  }
}

void loop() {
  powerCycleTest();
  delay(2000);  // Pause between full test cycles
}
