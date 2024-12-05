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
  delay(2000);
}

void loop() {
  Serial.println("\n--- Testing Forward Movement ---");
  Serial.println("Right Motor: IN1=HIGH, IN2=LOW");
  Serial.println("Left Motor: IN3=LOW, IN4=HIGH");
  
  // Right motor forward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  // Left motor forward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  delay(3000);
  
  Serial.println("\n--- Testing Stop ---");
  // Stop both motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  delay(2000);
  
  Serial.println("\n--- Testing Backward Movement ---");
  Serial.println("Right Motor: IN1=LOW, IN2=HIGH");
  Serial.println("Left Motor: IN3=HIGH, IN4=LOW");
  
  // Right motor backward
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  // Left motor backward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  delay(3000);
  
  Serial.println("\n--- Testing Stop ---");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  delay(2000);
}
