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
  
  Serial.begin(9600);
  Serial.println("Wiring Test Starting...");
}

void testMotor(String name, int enable, int in1, int in2) {
  Serial.println("Testing " + name + " motor...");
  
  // Test forward
  Serial.println("Forward test...");
  analogWrite(enable, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(2000);
  
  // Stop
  Serial.println("Stop test...");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enable, 0);
  delay(1000);
  
  // Test backward
  Serial.println("Backward test...");
  analogWrite(enable, 200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(2000);
  
  // Stop
  Serial.println("Stop test...");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enable, 0);
  delay(1000);
  
  Serial.println(name + " motor test complete\n");
}

void loop() {
  Serial.println("\n=== Starting Right Motor Test ===");
  testMotor("Right", ENA, IN1, IN2);
  delay(2000);
  
  Serial.println("\n=== Starting Left Motor Test ===");
  testMotor("Left", ENB, IN3, IN4);
  delay(2000);
  
  Serial.println("\nAll tests complete. Waiting 5 seconds before next round...");
  delay(5000);
}
