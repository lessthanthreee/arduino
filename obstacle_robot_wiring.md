# Obstacle Avoiding Robot - Wiring Diagram

## Components Used
- Arduino UNO
- Sensor Shield V5
- L298N Motor Driver (the "red board")
- HC-SR04 Ultrasonic Sensor
- 2x Line Detector Sensors
- 2x DC Motors with wheels
- 4x Batteries (assuming AA batteries for motor power)
- 1x 9V Battery (for Arduino power)
- Transparent base/chassis

## Wiring Instructions

### L298N Motor Driver Connections:
1. Power Connections:
   - VCC: Connect to +12V (battery pack of 4 batteries)
   - GND: Connect to battery ground
   - 5V: This will power the logic circuits

2. Motor Connections:
   - OUT1, OUT2: Right Motor
   - OUT3, OUT4: Left Motor

3. Control Pins to Arduino:
   - ENA (Enable A) → Arduino Pin 10
   - IN1 → Arduino Pin 9
   - IN2 → Arduino Pin 8
   - IN3 → Arduino Pin 7
   - IN4 → Arduino Pin 6
   - ENB (Enable B) → Arduino Pin 5

### HC-SR04 Ultrasonic Sensor:
- VCC → 5V from Sensor Shield
- GND → GND from Sensor Shield
- TRIG → Arduino Pin 12
- ECHO → Arduino Pin 11

### Line Detector Sensors:
Right Sensor:
- VCC → 5V from Sensor Shield
- GND → GND from Sensor Shield
- OUT → Arduino Pin A0

Left Sensor:
- VCC → 5V from Sensor Shield
- GND → GND from Sensor Shield
- OUT → Arduino Pin A1

### Power Supply:
- Connect 9V battery to Arduino's power jack
- Connect 4-battery pack (6V) to L298N's power input

## Safety Notes:
1. Double-check all connections before powering on
2. Ensure proper polarity of all connections
3. Keep wires neat and secured to prevent interference with moving parts
4. Make sure motors are properly mounted to the chassis
5. Test each component individually before final assembly
