# define ENB 10  // Left motor speed
# define IN3 9   // Left motor direction
# define IN4 8   // Left motor direction

const int MOTOR_SPEED = 200;

void setup() {
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);
  delay(2000);
  Serial.println("Left Wheel Basic Test");
}

void loop() {
  Serial.println("\n--- Moving Forward ---");
  // Left motor forward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  delay(2000);
  
  Serial.println("--- Stopping ---");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  
  delay(1000);
  
  Serial.println("--- Moving Backward ---");
  // Left motor backward
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  delay(2000);
  
  Serial.println("--- Stopping ---");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  
  delay(1000);
}
