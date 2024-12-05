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
  
  // Servo Setup
  servo_motor.attach(SERVO_PIN);
  servo_motor.write(90);  // Center position
  
  Serial.println("SENSOR-MOTOR INTERFERENCE TEST");
}

void leftWheelForward() {
  Serial.println("LEFT WHEEL FORWARD");
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void leftWheelStop() {
  Serial.println("LEFT WHEEL STOP");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void servoTest() {
  Serial.println("SERVO TEST");
  servo_motor.write(0);   // Right
  delay(500);
  
  servo_motor.write(90);  // Center
  delay(500);
  
  servo_motor.write(180); // Left
  delay(500);
  
  servo_motor.write(90);  // Back to center
}

void sensorTest() {
  Serial.println("SENSOR DISTANCE TEST");
  int distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void loop() {
  static int testPhase = 0;
  
  switch(testPhase) {
    case 0:
      Serial.println("\n--- MOTOR ONLY ---");
      leftWheelForward();
      delay(2000);
      leftWheelStop();
      break;
    
    case 1:
      Serial.println("\n--- SERVO ONLY ---");
      servoTest();
      break;
    
    case 2:
      Serial.println("\n--- SENSOR ONLY ---");
      sensorTest();
      break;
    
    case 3:
      Serial.println("\n--- MOTOR + SERVO ---");
      leftWheelForward();
      servoTest();
      leftWheelStop();
      break;
    
    case 4:
      Serial.println("\n--- MOTOR + SENSOR ---");
      leftWheelForward();
      sensorTest();
      leftWheelStop();
      break;
    
    case 5:
      Serial.println("\n--- ALL COMPONENTS ---");
      leftWheelForward();
      servoTest();
      sensorTest();
      leftWheelStop();
      break;
  }
  
  testPhase = (testPhase + 1) % 6;
  delay(2000);
}
