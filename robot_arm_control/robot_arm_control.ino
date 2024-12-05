#include <Servo.h>

// Create servo objects
Servo baseServo;      // Controls the base rotation (pin 9)
Servo shoulderServo;  // Controls shoulder joint (pin 10)
Servo elbowServo;     // Controls elbow joint (pin 11)
Servo gripperServo;   // Controls the gripper (pin 12)

// Define initial positions
int basePos = 90;     // Center position
int shoulderPos = 90; // Neutral position
int elbowPos = 90;    // Neutral position
int gripperPos = 90;  // Open position

// Define positions for picking and placing
const int PICK_BASE = 90;      // Front position
const int PLACE_BASE = 180;    // Back position
const int SHOULDER_DOWN = 130; // Down position for picking
const int SHOULDER_UP = 60;    // Up position for carrying
const int ELBOW_EXTEND = 45;   // Extended position
const int ELBOW_RETRACT = 120; // Retracted position
const int GRIPPER_OPEN = 140;  // Open position
const int GRIPPER_CLOSE = 70;  // Closed position around ball

void setup() {
  // Attach servos to their respective pins
  baseServo.attach(9);
  shoulderServo.attach(10);
  elbowServo.attach(11);
  gripperServo.attach(12);
  
  // Move to initial position
  moveToNeutral();
  delay(2000);
}

void loop() {
  pickAndPlaceBall();
  delay(5000); // Wait 5 seconds before repeating
}

void moveToNeutral() {
  // Move all servos to neutral position
  baseServo.write(90);
  shoulderServo.write(90);
  elbowServo.write(90);
  gripperServo.write(GRIPPER_OPEN);
}

void moveSlowly(Servo &servo, int startPos, int endPos, int delayTime) {
  // Move servo slowly from start to end position
  if (startPos < endPos) {
    for (int pos = startPos; pos <= endPos; pos++) {
      servo.write(pos);
      delay(delayTime);
    }
  } else {
    for (int pos = startPos; pos >= endPos; pos--) {
      servo.write(pos);
      delay(delayTime);
    }
  }
}

void pickAndPlaceBall() {
  // 1. Move to front position
  moveSlowly(baseServo, basePos, PICK_BASE, 15);
  delay(500);
  
  // 2. Open gripper
  moveSlowly(gripperServo, gripperPos, GRIPPER_OPEN, 15);
  delay(500);
  
  // 3. Lower arm to pick position
  moveSlowly(shoulderServo, shoulderPos, SHOULDER_DOWN, 15);
  moveSlowly(elbowServo, elbowPos, ELBOW_EXTEND, 15);
  delay(500);
  
  // 4. Close gripper to grab ball
  moveSlowly(gripperServo, GRIPPER_OPEN, GRIPPER_CLOSE, 15);
  delay(1000);
  
  // 5. Lift arm
  moveSlowly(shoulderServo, SHOULDER_DOWN, SHOULDER_UP, 15);
  moveSlowly(elbowServo, ELBOW_EXTEND, ELBOW_RETRACT, 15);
  delay(500);
  
  // 6. Rotate to back position
  moveSlowly(baseServo, PICK_BASE, PLACE_BASE, 15);
  delay(500);
  
  // 7. Lower arm to place position
  moveSlowly(shoulderServo, SHOULDER_UP, SHOULDER_DOWN, 15);
  moveSlowly(elbowServo, ELBOW_RETRACT, ELBOW_EXTEND, 15);
  delay(500);
  
  // 8. Open gripper to release ball
  moveSlowly(gripperServo, GRIPPER_CLOSE, GRIPPER_OPEN, 15);
  delay(500);
  
  // 9. Return to neutral position
  moveSlowly(shoulderServo, SHOULDER_DOWN, 90, 15);
  moveSlowly(elbowServo, ELBOW_EXTEND, 90, 15);
  moveSlowly(baseServo, PLACE_BASE, 90, 15);
  
  // Update current positions
  basePos = 90;
  shoulderPos = 90;
  elbowPos = 90;
  gripperPos = GRIPPER_OPEN;
}
