# define TRIG_PIN 12
# define ECHO_PIN 11

// Motor A (Right)
# define ENA 10
# define IN1 9
# define IN2 8

// Motor B (Left)
# define ENB 5
# define IN3 7
# define IN4 6

// Constants
const int OBSTACLE_DISTANCE = 20;  // Distance in cm to react
const int TURN_TIME = 750;         // Time to turn (milliseconds)

void setup() {
  // Ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Motor control pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);  // Start serial communication
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void forward() {
  // Right motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Left motor forward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Set speed for both motors
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void turnRight() {
  // Right motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Left motor forward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Set speed for both motors
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void loop() {
  int distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance < OBSTACLE_DISTANCE) {
    // Obstacle detected!
    Serial.println("Obstacle detected! Turning...");
    stop();
    delay(500);
    turnRight();
    delay(TURN_TIME);
    stop();
    delay(200);
  } else {
    // No obstacle, move forward
    forward();
  }
  
  delay(100);  // Small delay between readings
}
