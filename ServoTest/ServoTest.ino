#include <Servo.h>

#define SERVO_PIN 13

Servo myservo;  // Create servo object
int pos = 0;    // Variable to store the servo position

void setup() {
  myservo.attach(SERVO_PIN);  // Attaches the servo to pin 13
  Serial.begin(9600);
  Serial.println("Servo Test Starting...");
}

void loop() {
  // Sweep from 0 to 180 degrees
  Serial.println("Sweeping right...");
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  delay(1000);  // Wait at right position
  
  // Sweep from 180 to 0 degrees
  Serial.println("Sweeping left...");
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
  delay(1000);  // Wait at left position
}
