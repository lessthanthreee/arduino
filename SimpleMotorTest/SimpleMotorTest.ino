// Motor A
#define ENA 10
#define IN1 9
#define IN2 8

void setup() {
  // Set all motor pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Start with motors off
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop() {
  // Turn on motor A
  analogWrite(ENA, 255);  // Full speed
  
  // Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(3000);  // Run for 3 seconds
  
  // Stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(2000);  // Wait 2 seconds
  
  // Backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(3000);  // Run for 3 seconds
  
  // Stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(2000);  // Wait 2 seconds
}
