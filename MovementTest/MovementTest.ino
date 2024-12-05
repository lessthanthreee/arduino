# define ENA 10  // Right motor speed
# define IN3 9   // Right motor direction
# define IN4 8   // Right motor direction
# define ENB 5   // Left motor speed
# define IN1 7   // Left motor direction
# define IN2 6   // Left motor direction

const int MOTOR_SPEED = 200;  // Adjust between 0-255
const int MOVE_TIME = 2000;   // How long to perform each movement

void setup() {
  // Initialize motor control pins
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  Serial.begin(9600);
  delay(2000);  // Initial delay
}

void loop() {
  Serial.println("Moving Forward...");
  moveForward();
  delay(MOVE_TIME);
  
  Serial.println("Stopping...");
  stopMotors();
  delay(1000);
  
  Serial.println("Moving Backward...");
  moveBackward();
  delay(MOVE_TIME);
  
  Serial.println("Stopping...");
  stopMotors();
  delay(1000);
  
  Serial.println("Turning Right...");
  turnRight();
  delay(MOVE_TIME);
  
  Serial.println("Stopping...");
  stopMotors();
  delay(1000);
  
  Serial.println("Turning Left...");
  turnLeft();
  delay(MOVE_TIME);
  
  Serial.println("Stopping...");
  stopMotors();
  delay(1000);
}

void stopMotors() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void moveForward() {
  // Right motor forward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  // Left motor forward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void moveBackward() {
  // Right motor backward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  // Left motor backward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void turnRight() {
  // Right motor backward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  // Left motor forward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void turnLeft() {
  // Right motor forward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  // Left motor backward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}
