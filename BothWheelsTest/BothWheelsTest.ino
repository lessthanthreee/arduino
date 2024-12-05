#define ENA 10  // Right motor speed
#define IN1 9   // Right motor direction
#define IN2 8   // Right motor direction
#define ENB 5   // Left motor speed
#define IN3 7   // Left motor direction
#define IN4 6   // Left motor direction

void setup() {
  // Set all motor pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // Move both motors forward
  analogWrite(ENA, 200);  // Right motor speed
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); // Right motor forward

  analogWrite(ENB, 200);  // Left motor speed
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); // Left motor forward

  delay(3000);  // Run for 3 seconds

  // Stop both motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  delay(2000);  // Wait 2 seconds before repeating
}
