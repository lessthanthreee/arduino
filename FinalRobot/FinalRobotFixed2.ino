#include <Servo.h>

// Motor pins (exactly as in working test)
#define ENA 10  // Right motor speed
#define IN1 9   // Right motor direction
#define IN2 8   // Right motor direction
#define ENB 5   // Left motor speed
#define IN3 7   // Left motor direction
#define IN4 6   // Left motor direction

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
  // Right motor forward (exactly as in working test)
  analogWrite(ENA, MOTOR_SPEED);  // Right motor speed
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); // Right motor forward

  // Left motor forward (exactly as in working test)
  analogWrite(ENB, MOTOR_SPEED);  // Left motor speed
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); // Left motor forward
}

void stop() {
  // Stop both motors (exactly as in working test)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void turnRight() {
  // Right motor backward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  // Left motor forward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
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