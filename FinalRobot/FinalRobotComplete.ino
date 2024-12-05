#include <Servo.h>

// Motor pins (corrected left/right assignments)
#define ENA 10  // Left motor speed
#define IN1 9   // Left motor direction
#define IN2 8   // Left motor direction
#define ENB 5   // Right motor speed
#define IN3 7   // Right motor direction
#define IN4 6   // Right motor direction

// Sensor pins
#define SERVO_PIN 13
#define TRIG_PIN 12
#define ECHO_PIN 11

// Constants
const int OBSTACLE_DISTANCE = 20;  // cm
const int MOTOR_SPEED = 200;      // 0-255
const int TURN_TIME = 750;        // ms

Servo myservo;
int servoPos = 90;  // Center position

void setup() {
  // Initialize servo
  myservo.attach(SERVO_PIN);
  myservo.write(90);  // Center position
  
  // Initialize ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize motor pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Optional: Serial for debugging
  Serial.begin(9600);
  
  // Initial delay to position robot
  delay(2000);
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void forward() {
  // Left motor forward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  // Right motor forward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stop() {
  // Stop both motors
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  // Left motor forward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  // Right motor backward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void scanArea() {
  // Scan right
  for(int i = 90; i <= 180; i += 10) {
    myservo.write(i);
    delay(100);
    if(getDistance() > OBSTACLE_DISTANCE) {
      return; // Found clear path
    }
  }
  
  // Scan left
  for(int i = 180; i >= 0; i -= 10) {
    myservo.write(i);
    delay(100);
    if(getDistance() > OBSTACLE_DISTANCE) {
      return; // Found clear path
    }
  }
  
  // Return to center
  myservo.write(90);
}

void loop() {
  // Check forward distance
  myservo.write(90);
  delay(100);
  int distance = getDistance();
  
  // Print distance (optional)
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if (distance < OBSTACLE_DISTANCE) {
    // Obstacle detected
    stop();
    delay(200);
    
    // Scan area for clear path
    scanArea();
    
    // Turn right and continue
    turnRight();
    delay(TURN_TIME);
    stop();
    delay(200);
  } else {
    // No obstacle, move forward
    forward();
  }
  
  delay(50);  // Small delay between readings
}
