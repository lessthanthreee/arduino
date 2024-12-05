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
  // Test Right Motor
  analogWrite(ENA, 200);  // Set speed
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); // Move forward
  delay(2000);            // Run for 2 seconds
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW); // Stop
  delay(1000);            // Wait 1 second
  
  // Test Left Motor
  analogWrite(ENB, 200);  // Set speed
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); // Move forward
  delay(2000);            // Run for 2 seconds
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW); // Stop
  delay(1000);            // Wait 1 second
}
