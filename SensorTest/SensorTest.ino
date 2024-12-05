#include <NewPing.h>

// Please tell me which pins you moved TRIG and ECHO to
#define TRIG_PIN 11  // CHANGE THIS to your new TRIG pin
#define ECHO_PIN 12  // CHANGE THIS to your new ECHO pin
#define MAX_DISTANCE 200

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Ultrasonic Sensor Test");
}

void loop() {
  delay(500);
  
  int distance = sonar.ping_cm();
  
  Serial.print("Distance = ");
  if (distance == 0) {
    Serial.println("Out of range or sensor error");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }
}
