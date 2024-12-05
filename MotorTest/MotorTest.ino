# define ENA 10
# define IN1 9
# define IN2 8
# define IN3 7
# define IN4 6
# define ENB 5

void setup() {
  // Set all the motor control pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Initially stop all motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
  // Start serial for debugging
  Serial.begin(9600);
  Serial.println("Motor test starting...");
}

void loop() {
  Serial.println("Testing Motor A (IN1/IN2)...");
  
  // Enable Motor A at half speed
  analogWrite(ENA, 128);
  
  // Motor A forward
  Serial.println("Motor A forward");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(2000);
  
  // Stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(1000);
  
  // Motor A backward
  Serial.println("Motor A backward");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(2000);
  
  // Stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(1000);
  
  Serial.println("Testing Motor B (IN3/IN4)...");
  
  // Enable Motor B at half speed
  analogWrite(ENB, 128);
  
  // Motor B forward
  Serial.println("Motor B forward");
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(2000);
  
  // Stop
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(1000);
  
  // Motor B backward
  Serial.println("Motor B backward");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(2000);
  
  // Stop all
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(2000);
  
  Serial.println("Test cycle complete!");
}
