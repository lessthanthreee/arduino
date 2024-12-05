#define TRIG_PIN 12
#define ECHO_PIN 11

void setup() {
  Serial.begin(9600);  // Start serial communication
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

int getDistance() {
  // Clear the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Send trigger pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the echo pin, convert time to distance in cm
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;  // Speed of sound / 2 (round trip)
}

void loop() {
  // Get and print the distance
  int distance = getDistance();
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(500);  // Wait half second before next reading
}
