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
  delay(2000);
  
  // Motor Pin Diagnostic Setup
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Servo Setup
  servo_motor.attach(SERVO_PIN);
  servo_motor.write(90);  // Center position
  
  Serial.println("LEFT WHEEL COMPREHENSIVE DIAGNOSTICS");
  Serial.println("-------------------------------------");
}

void printPinStates() {
  Serial.println("\n--- PIN STATE VERIFICATION ---");
  Serial.print("ENB (Speed) Pin State: "); Serial.println(digitalRead(ENB));
  Serial.print("IN3 (Direction 1) Pin State: "); Serial.println(digitalRead(IN3));
  Serial.print("IN4 (Direction 2) Pin State: "); Serial.println(digitalRead(IN4));
}

void motorVoltageTest() {
  Serial.println("\n--- MOTOR VOLTAGE DIAGNOSTIC ---");
  
  int testSpeeds[] = {50, 100, 150, 200, 255};
  
  for (int i = 0; i < 5; i++) {
    Serial.print("\nTesting Motor Speed: ");
    Serial.println(testSpeeds[i]);
    
    // Reset motor state
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
    delay(50);
    
    // Set motor direction
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
    // Apply speed
    analogWrite(ENB, testSpeeds[i]);
    
    // Diagnostic information
    printPinStates();
    
    // Run for short duration
    delay(1000);
    
    // Stop motor
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
    
    delay(500);
  }
}

void sensorInterferenceTest() {
  Serial.println("\n--- SENSOR INTERFERENCE DIAGNOSTIC ---");
  
  int testSpeeds[] = {50, 100, 255};
  
  for (int i = 0; i < 3; i++) {
    Serial.print("\nTesting Speed: ");
    Serial.println(testSpeeds[i]);
    
    // Motor setup
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, testSpeeds[i]);
    
    // Servo sweep
    int sweepAngles[] = {0, 90, 180};
    for (int j = 0; j < 3; j++) {
      servo_motor.write(sweepAngles[j]);
      delay(500);
      
      // Ping distance
      int distance = sonar.ping_cm();
      Serial.print("Angle: ");
      Serial.print(sweepAngles[j]);
      Serial.print(" | Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
      
      // Detailed motor state check
      printPinStates();
    }
    
    // Stop motor
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
    
    delay(1000);
  }
}

void powerSupplyTest() {
  Serial.println("\n--- POWER SUPPLY DIAGNOSTIC ---");
  
  // Check voltage at different motor states
  Serial.println("Measuring voltage during motor operation");
  
  // Motor at different speeds
  int testSpeeds[] = {50, 100, 255};
  
  for (int i = 0; i < 3; i++) {
    Serial.print("\nMotor Speed: ");
    Serial.println(testSpeeds[i]);
    
    // Motor setup
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, testSpeeds[i]);
    
    // Simulate sensor load
    servo_motor.write(90);
    sonar.ping_cm();
    
    delay(1000);
    
    // Stop motor
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
    
    delay(500);
  }
}

void loop() {
  motorVoltageTest();
  sensorInterferenceTest();
  powerSupplyTest();
  
  // Prevent repeated tests
  while(1) {
    delay(10000);
  }
}
