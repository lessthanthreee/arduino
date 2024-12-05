# define ENB 10  // Left motor speed
# define IN3 9   // Left motor direction
# define IN4 8   // Left motor direction

void setup() {
  Serial.begin(9600);
  
  // VERBOSE Pin Configuration
  Serial.println("LEFT WHEEL PIN TEST");
  Serial.print("ENB (speed pin): "); Serial.println(ENB);
  Serial.print("IN3 (direction pin 1): "); Serial.println(IN3);
  Serial.print("IN4 (direction pin 2): "); Serial.println(IN4);
  
  // Set all pins as OUTPUT
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Initial state
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void testMotorMovement(int speed) {
  Serial.println("\n--- MOTOR MOVEMENT TEST ---");
  Serial.print("Testing with speed: "); Serial.println(speed);
  
  // Forward Test
  Serial.println("FORWARD TEST");
  Serial.println("IN3: HIGH, IN4: LOW");
  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  delay(2000);
  
  // Stop
  Serial.println("STOPPING");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  
  delay(1000);
  
  // Backward Test
  Serial.println("BACKWARD TEST");
  Serial.println("IN3: LOW, IN4: HIGH");
  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  delay(2000);
  
  // Stop
  Serial.println("STOPPING");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  
  delay(1000);
}

void loop() {
  // Test with different speeds
  testMotorMovement(100);   // Low speed
  testMotorMovement(200);   // Medium speed
  testMotorMovement(255);   // Full speed
}
