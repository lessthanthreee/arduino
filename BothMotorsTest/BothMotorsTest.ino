# define ENA 10  // Right motor speed
# define ENB 5   // Left motor speed
# define IN1 9   // Right motor direction
# define IN2 8   // Right motor direction
# define IN3 7   // Left motor direction
# define IN4 6   // Left motor direction

void setup() {
  // Set all motor pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void forward() {
  // Right motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Left motor forward (reversed)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Set speed for both motors
  analogWrite(ENA, 200);  // Right motor speed
  analogWrite(ENB, 200);  // Left motor speed
}

void stop() {
  // Stop both motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void loop() {
  // Move forward for 3 seconds
  forward();
  delay(3000);
  
  // Stop for 2 seconds
  stop();
  delay(2000);
}
