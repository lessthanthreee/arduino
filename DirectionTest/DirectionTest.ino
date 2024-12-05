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
  Serial.println("\n--- Testing Forward Movement (CORRECTED) ---");
  
  // Right motor forward (SWAPPED)
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, LOW);    // Changed to LOW
  digitalWrite(IN2, HIGH);   // Changed to HIGH
  
  // Left motor forward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);   // Changed to HIGH
  digitalWrite(IN4, LOW);    // Changed to LOW
  
  delay(3000);
  
  // Stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  delay(2000);
  
  Serial.println("\n--- Testing Backward Movement (CORRECTED) ---");
  
  // Right motor backward (SWAPPED)
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);   // Changed to HIGH
  digitalWrite(IN2, LOW);    // Changed to LOW
  
  // Left motor backward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, LOW);    // Changed to LOW
  digitalWrite(IN4, HIGH);   // Changed to HIGH
  
  delay(3000);
  
  // Stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  delay(2000);
}
