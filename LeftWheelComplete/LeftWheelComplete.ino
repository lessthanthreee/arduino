#include <Servo.h>
#include <NewPing.h>

// Left motor pins (verified working)
#define ENB 10  // Left motor speed
#define IN3 9   // Left motor direction
#define IN4 8   // Left motor direction

// Sensor pins (verified working)
#define SERVO_PIN 3    // Servo on pin 3
#define TRIG_PIN 2     // Ultrasonic TRIG on pin 2
#define ECHO_PIN 4     // Ultrasonic ECHO on pin 4

const int MOTOR_SPEED = 200;
const int OBSTACLE_DISTANCE = 15;  // cm
const int MAXIMUM_DISTANCE = 200;  // cm

NewPing sonar(TRIG_PIN, ECHO_PIN, MAXIMUM_DISTANCE);
Servo servo_motor;

void setup() {
  // Left motor setup
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Servo setup
  servo_motor.attach(SERVO_PIN);
  servo_motor.write(90);  // Center position
  
  Serial.begin(9600);
  delay(2000);
  Serial.println("Left Wheel + Sensors Test");
}

// Verified working motor functions
void leftWheelForward() {
  Serial.println("LEFT WHEEL FORWARD - FULL DEBUG");
  Serial.print("ENB (speed): "); Serial.println(MOTOR_SPEED);
  Serial.print("IN3: HIGH, IN4: LOW");
  
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  delay(10);  // Short delay to ensure signal stability
  Serial.println("Left wheel forward");
}

void leftWheelBackward() {
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Left wheel backward");
}

void leftWheelStop() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  Serial.println("Left wheel stop");
}

// Sensor functions
int getDistance() {
  int distance = sonar.ping_cm();
  if (distance == 0) distance = MAXIMUM_DISTANCE;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

int lookDirection(int angle) {
  Serial.print("Looking at angle: ");
  Serial.println(angle);
  
  servo_motor.write(angle);
  delay(500);  // Wait for servo to move
  
  int distance = getDistance();
  delay(100);
  
  return distance;
}

void loop() {
  Serial.println("\n--- Starting new scan ---");
  
  // FORCE MOVEMENT FOR TESTING
  leftWheelForward();
  delay(2000);
  leftWheelStop();
  delay(1000);
  
  // Commented out original obstacle detection logic
  /*
  servo_motor.write(90);
  delay(500);
  int frontDistance = getDistance();
  
  if (frontDistance < OBSTACLE_DISTANCE) {
    Serial.println("Obstacle detected! Stopping...");
    leftWheelStop();
    delay(500);
    
    // Back up a bit
    Serial.println("Backing up...");
    leftWheelBackward();
    delay(1000);
    leftWheelStop();
    delay(500);
    
    // Look right (0 degrees)
    int rightDistance = lookDirection(0);
    delay(500);
    
    // Look left (180 degrees)
    int leftDistance = lookDirection(180);
    delay(500);
    
    // Return to center
    servo_motor.write(90);
    delay(500);
    
    // Choose direction based on distances
    Serial.println("\nDistance Summary:");
    Serial.print("Right: "); Serial.println(rightDistance);
    Serial.print("Left: "); Serial.println(leftDistance);
    
    if (rightDistance > leftDistance) {
      Serial.println("More space on right - moving forward");
      leftWheelForward();
    } else {
      Serial.println("More space on left - moving backward");
      leftWheelBackward();
    }
    delay(750);  // Turn duration
    leftWheelStop();
    
  } else {
    // No obstacle, move forward
    leftWheelForward();
  }
  
  delay(100);  // Small delay between readings
  */
}
