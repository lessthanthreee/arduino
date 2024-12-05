#include <Servo.h>
#include <NewPing.h>

// Motor Pins
#define ENA 5   // Right motor speed
#define IN1 7   // Right motor direction
#define IN2 6   // Right motor direction
#define ENB 10  // Left motor speed
#define IN3 9   // Left motor direction
#define IN4 8   // Left motor direction

// Line Sensor Pins
#define LEFT_LINE_SENSOR A0
#define RIGHT_LINE_SENSOR A1

// Sensor Pins
#define SERVO_PIN 3
#define TRIG_PIN 2
#define ECHO_PIN 4

// Constants
#define MAXIMUM_DISTANCE 200
#define FULL_SPEED 255

// Sensor Objects
NewPing sonar(TRIG_PIN, ECHO_PIN, MAXIMUM_DISTANCE);
Servo servo_motor;

void setup() {
  Serial.begin(9600);
  
  // Motor Pin Setup
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Line Sensor Setup
  pinMode(LEFT_LINE_SENSOR, INPUT);
  pinMode(RIGHT_LINE_SENSOR, INPUT);
  
  // Servo Setup
  servo_motor.attach(SERVO_PIN);
  
  Serial.println("ROBOT SENSOR CALIBRATION SYSTEM");
  delay(2000);
}

void servoCalibration() {
  Serial.println("\n--- SERVO CALIBRATION ---");
  
  int angles[] = {0, 45, 90, 135, 180};
  
  for (int angle : angles) {
    servo_motor.write(angle);
    Serial.print("Servo Angle: ");
    Serial.println(angle);
    delay(1000);
  }
}

void ultrasonicDistanceTest() {
  Serial.println("\n--- ULTRASONIC DISTANCE TEST ---");
  
  int testAngles[] = {0, 45, 90, 135, 180};
  
  for (int angle : testAngles) {
    servo_motor.write(angle);
    delay(500);
    
    // Multiple distance readings
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" | Distances: ");
    
    for (int i = 0; i < 5; i++) {
      int distance = sonar.ping_cm();
      Serial.print(distance);
      Serial.print(" ");
      delay(100);
    }
    Serial.println(" cm");
  }
}

void lineSensorTest() {
  Serial.println("\n--- LINE SENSOR CALIBRATION ---");
  
  Serial.println("Place robot on different surfaces:");
  Serial.println("1. White surface");
  Serial.println("2. Black surface");
  Serial.println("3. Mixed/transition surface");
  
  for (int i = 0; i < 50; i++) {
    int leftValue = analogRead(LEFT_LINE_SENSOR);
    int rightValue = analogRead(RIGHT_LINE_SENSOR);
    
    Serial.print("Left Sensor: ");
    Serial.print(leftValue);
    Serial.print(" | Right Sensor: ");
    Serial.println(rightValue);
    
    delay(200);
  }
}

void fullSpeedMotorTest() {
  Serial.println("\n--- FULL SPEED MOTOR TEST ---");
  
  // Right Motor Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, FULL_SPEED);
  
  // Left Motor Forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, FULL_SPEED);
  
  Serial.println("Moving Forward at Full Speed");
  delay(2000);
  
  // Stop Motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  
  Serial.println("Motors Stopped");
}

void loop() {
  servoCalibration();
  delay(2000);
  
  ultrasonicDistanceTest();
  delay(2000);
  
  lineSensorTest();
  delay(2000);
  
  fullSpeedMotorTest();
  
  // Prevent repeated tests
  while(1) {
    delay(10000);
  }
}
