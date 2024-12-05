#define TRIG_PIN 12
#define ECHO_PIN 11
#define ENA 10
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define ENB 5
#define RIGHT_LINE_SENSOR A0
#define LEFT_LINE_SENSOR A1

// Constants for obstacle avoidance
const int OBSTACLE_DISTANCE = 20; // Distance in cm
const int TURN_DELAY = 750;      // Delay for turning
const int MOTOR_SPEED = 200;     // Motor speed (0-255)

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Configure ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Configure motor driver pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Configure line sensor pins
  pinMode(RIGHT_LINE_SENSOR, INPUT);
  pinMode(LEFT_LINE_SENSOR, INPUT);
}

// Function to measure distance using ultrasonic sensor
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2; // Convert to centimeters
}

// Motor control functions
void moveForward() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  int distance = getDistance();
  int rightLineSensor = analogRead(RIGHT_LINE_SENSOR);
  int leftLineSensor = analogRead(LEFT_LINE_SENSOR);
  
  // Print sensor values for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("cm, Right Line: ");
  Serial.print(rightLineSensor);
  Serial.print(", Left Line: ");
  Serial.println(leftLineSensor);
  
  // Check for obstacles
  if (distance < OBSTACLE_DISTANCE) {
    stopMotors();
    delay(500);
    moveBackward();
    delay(500);
    
    // Random turn direction when obstacle detected
    if (random(2) == 0) {
      turnLeft();
    } else {
      turnRight();
    }
    delay(TURN_DELAY);
  }
  // Check line sensors (adjust threshold value based on your sensors)
  else if (rightLineSensor < 500 || leftLineSensor < 500) {
    if (rightLineSensor < leftLineSensor) {
      turnLeft();
      delay(TURN_DELAY/2);
    } else {
      turnRight();
      delay(TURN_DELAY/2);
    }
  }
  else {
    moveForward();
  }
  
  delay(100); // Small delay to prevent sensor reading overflow
}
