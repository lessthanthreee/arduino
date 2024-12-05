# define ENA 5   // Right motor speed
# define IN1 7   // Right motor direction
# define IN2 6   // Right motor direction
# define ENB 10  // Left motor speed
# define IN3 9   // Left motor direction
# define IN4 8   // Left motor direction

const int MOTOR_SPEED = 200;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Testing with corrected directions");
}

void loop() {
  Serial.println("Moving Forward");
  
  // Right motor forward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  // Left motor forward (reversed HIGH/LOW)
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, LOW);  // Changed from HIGH
  digitalWrite(IN4, HIGH); // Changed from LOW
  
  delay(3000);
  
  Serial.println("Stopping");
  // Stop both motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  delay(2000);
  
  Serial.println("Moving Backward");
  
  // Right motor backward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  // Left motor backward (reversed HIGH/LOW)
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);  // Changed from LOW
  digitalWrite(IN4, LOW);   // Changed from HIGH
  
  delay(3000);
  
  Serial.println("Stopping");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  delay(2000);
}
