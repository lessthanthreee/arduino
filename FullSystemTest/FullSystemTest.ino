#include <Servo.h>
#include <NewPing.h>

// RIGHT Motor Pins
#define ENA 5   // Right motor speed
#define IN1 7   // Right motor direction
#define IN2 6   // Right motor direction

// LEFT Motor Pins
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
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Servo Setup
  servo_motor.attach(SERVO_PIN);
  servo_motor.write(90);  // Center position
  
  Serial.println("FULL SYSTEM TEST INITIALIZED");
}

// RIGHT WHEEL ONLY
void rightWheelForward() {
  Serial.println("RIGHT WHEEL FORWARD");
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void rightWheelBackward() {
  Serial.println("RIGHT WHEEL BACKWARD");
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void rightWheelStop() {
  Serial.println("RIGHT WHEEL STOP");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

// LEFT WHEEL ONLY
void leftWheelForward() {
  Serial.println("LEFT WHEEL FORWARD");
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void leftWheelBackward() {
  Serial.println("LEFT WHEEL BACKWARD");
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void leftWheelStop() {
  Serial.println("LEFT WHEEL STOP");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

// SENSOR FUNCTIONS
int getDistance() {
  int distance = sonar.ping_cm();
  if (distance == 0) distance = MAXIMUM_DISTANCE;
  Serial.print("DISTANCE: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

void servoSweep() {
  Serial.println("SERVO SWEEP TEST");
  servo_motor.write(0);   // Right
  delay(500);
  getDistance();
  
  servo_motor.write(90);  // Center
  delay(500);
  getDistance();
  
  servo_motor.write(180); // Left
  delay(500);
  getDistance();
  
  servo_motor.write(90);  // Back to center
}

void loop() {
  static int testPhase = 0;
  
  switch(testPhase) {
    case 0:
      Serial.println("\n--- RIGHT WHEEL ONLY TEST ---");
      rightWheelForward();
      delay(2000);
      rightWheelStop();
      break;
    
    case 1:
      Serial.println("\n--- LEFT WHEEL ONLY TEST ---");
      leftWheelForward();
      delay(2000);
      leftWheelStop();
      break;
    
    case 2:
      Serial.println("\n--- RIGHT WHEEL WITH SENSORS ---");
      servoSweep();
      rightWheelForward();
      delay(2000);
      rightWheelStop();
      break;
    
    case 3:
      Serial.println("\n--- LEFT WHEEL WITH SENSORS ---");
      servoSweep();
      leftWheelForward();
      delay(2000);
      leftWheelStop();
      break;
  }
  
  testPhase = (testPhase + 1) % 4;
  delay(2000);
}
