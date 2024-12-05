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
const int MID_SPEED = 200;
const int LOW_SPEED = 100;
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
  
  Serial.println("MOTOR AND SENSOR SYNCHRONIZATION TEST");
}

void moveLeftWheel(int speed) {
  Serial.print("Moving Left Wheel at Speed: ");
  Serial.println(speed);
  
  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopLeftWheel() {
  Serial.println("Stopping Left Wheel");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void servoSweep() {
  Serial.println("Servo Sweep");
  servo_motor.write(0);   // Right
  delay(500);
  servo_motor.write(180); // Left
  delay(500);
  servo_motor.write(90);  // Center
}

void pingDistance() {
  int distance = sonar.ping_cm();
  Serial.print("Distance Ping: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void loop() {
  static int testCase = 0;
  
  switch(testCase) {
    case 0:
      Serial.println("\n--- TEST: Motor at MAX Speed, No Sensors ---");
      moveLeftWheel(MAX_SPEED);
      delay(2000);
      stopLeftWheel();
      break;
    
    case 1:
      Serial.println("\n--- TEST: Motor at MAX Speed with Servo Sweep ---");
      moveLeftWheel(MAX_SPEED);
      servoSweep();
      stopLeftWheel();
      break;
    
    case 2:
      Serial.println("\n--- TEST: Motor at MAX Speed with Distance Ping ---");
      moveLeftWheel(MAX_SPEED);
      pingDistance();
      stopLeftWheel();
      break;
    
    case 3:
      Serial.println("\n--- TEST: Motor at MAX Speed with Servo and Ping ---");
      moveLeftWheel(MAX_SPEED);
      servoSweep();
      pingDistance();
      stopLeftWheel();
      break;
    
    case 4:
      Serial.println("\n--- TEST: Motor at MID Speed with Servo and Ping ---");
      moveLeftWheel(MID_SPEED);
      servoSweep();
      pingDistance();
      stopLeftWheel();
      break;
    
    case 5:
      Serial.println("\n--- TEST: Motor at LOW Speed with Servo and Ping ---");
      moveLeftWheel(LOW_SPEED);
      servoSweep();
      pingDistance();
      stopLeftWheel();
      break;
  }
  
  testCase = (testCase + 1) % 6;
  delay(2000);
}
