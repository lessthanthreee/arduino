#include <NewPing.h>

#define TRIG_PIN 2  // Your TRIG pin
#define ECHO_PIN 4  // Your ECHO pin
#define MAX_DISTANCE 200

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Ultrasonic Only Test");
  Serial.println("TRIG on pin 2");
  Serial.println("ECHO on pin 4");
}

void loop() {
  delay(500);  // Wait half a second between pings
  
  unsigned int distance = sonar.ping_cm();
  
  Serial.print("Raw ping: ");
  Serial.print(sonar.ping());
  Serial.print(" | Distance: ");
  
  if (distance == 0) {
    Serial.println("No echo received - Check wiring!");
    Serial.println("Make sure:");
    Serial.println("1. TRIG (pin 2) connects to TRIG on sensor");
    Serial.println("2. ECHO (pin 4) connects to ECHO on sensor");
    Serial.println("3. VCC connects to 5V");
    Serial.println("4. GND connects to GND");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }
}
