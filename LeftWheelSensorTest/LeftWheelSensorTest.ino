#include <Servo.h>
#include <NewPing.h>

// Left motor pins only
#define ENB 10  // Left motor speed
#define IN3 9   // Left motor direction
#define IN4 8   // Left motor direction

// Sensor pins
#define SERVO_PIN 3
#define TRIG_PIN 2
#define ECHO_PIN 4

const int MOTOR_SPEED = 200;
const int OBSTACLE_DISTANCE = 20;
const int MAXIMUM_DISTANCE = 200;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAXIMUM_DISTANCE);
Servo servo_motor;

void setup() {
  // Left motor setup only
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Servo setup
  servo_motor.attach(SERVO_PIN);
  servo_motor.write(90);  // Center position
  
  Serial.begin(9600);
  delay(2000);
}

void leftWheelForward() {
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);   // Using our corrected direction
  digitalWrite(IN4, LOW);    // Using our corrected direction
  Serial.println("Left wheel forward");
}

void leftWheelBackward() {
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, LOW);    // Using our corrected direction
  digitalWrite(IN4, HIGH);   // Using our corrected direction
  Serial.println("Left wheel backward");
}

void leftWheelStop() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  Serial.println("Left wheel stop");
}

int lookRight() {
  servo_motor.write(10);
  delay(500);
  int distance = sonar.ping_cm();
  Serial.print("Right distance: ");
  Serial.println(distance);
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft() {
  servo_motor.write(170);
  delay(500);
  int distance = sonar.ping_cm();
  Serial.print("Left distance: ");
  Serial.println(distance);
  delay(100);
  servo_motor.write(90);
  return distance;
}

void loop() {
  int distance = sonar.ping_cm();
  
  if (distance == 0) {
    distance = MAXIMUM_DISTANCE;
  }
  
  Serial.print("Forward distance: ");
  Serial.println(distance);
  
  if (distance < OBSTACLE_DISTANCE) {
    // Obstacle detected!
    Serial.println("Obstacle detected!");
    
    // Stop and back up
    leftWheelStop();
    delay(500);
    leftWheelBackward();
    delay(1000);
    leftWheelStop();
    delay(500);
    
    // Look around
    int rightDistance = lookRight();
    delay(500);
    int leftDistance = lookLeft();
    delay(500);
    
    // Print distances for debugging
    Serial.println("Distances:");
    Serial.print("Right: "); Serial.println(rightDistance);
    Serial.print("Left: "); Serial.println(leftDistance);
    
    // Move left wheel based on readings
    if (rightDistance > leftDistance) {
      Serial.println("More space on right");
      leftWheelForward();  // This will help turn right
      delay(750);
    } else {
      Serial.println("More space on left");
      leftWheelBackward(); // This will help turn left
      delay(750);
    }
    leftWheelStop();
    delay(500);
  } else {
    leftWheelForward();
  }
  
  delay(100);  // Small delay between readings
}
