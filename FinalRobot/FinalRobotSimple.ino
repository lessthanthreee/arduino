#include <Servo.h>

// Motor pins - using exact working configuration
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

void setup() {
  // Motor setup
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Sensor setup
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myservo.attach(SERVO_PIN);
  myservo.write(90);
  
  Serial.begin(9600);
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

// Using exact pattern from working test
void forward() {
  // Right motor
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  // Left motor
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
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
  // Right motor backward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  // Left motor forward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void loop() {
  int distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if (distance < OBSTACLE_DISTANCE) {
    Serial.println("Obstacle detected!");
    stop();
    delay(500);
    
    turnRight();
    delay(TURN_TIME);
    stop();
    delay(200);
  } else {
    Serial.println("Moving forward");
    forward();
  }
  
  delay(100);
}
