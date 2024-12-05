# Arduino Obstacle Avoiding Robot - Wiring Diagram

## Components Required
- Arduino Uno
- L298N Motor Driver
- 2x DC Motors
- HC-SR04 Ultrasonic Sensor
- SG90 Servo Motor
- Power Supply (6-12V for motors)
- Jumper Wires

## Wiring Connections

### L298N Motor Driver
```
L298N Pin  ->  Arduino Pin
ENA        ->  Not used (jumpered)
IN1        ->  D5 (Left Motor Forward)
IN2        ->  D4 (Left Motor Backward)
IN3        ->  D3 (Right Motor Forward)
IN4        ->  D2 (Right Motor Backward)
ENB        ->  Not used (jumpered)
12V        ->  External Power Supply (+)
GND        ->  External Power Supply (-) and Arduino GND
```

### HC-SR04 Ultrasonic Sensor
```
HC-SR04 Pin  ->  Arduino Pin
VCC          ->  5V
Trig         ->  A3
Echo         ->  A2
GND          ->  GND
```

### Servo Motor
```
Servo Pin  ->  Arduino Pin
Signal     ->  D11
VCC        ->  5V
GND        ->  GND
```

## Visual Connection Diagram
```
                                    Arduino Uno
                                 +--------------+
                                 |              |
     HC-SR04                    |              |
    +--------+                  |              |
VCC-|        |-GND             |         GND--|
    |        |-Echo------------A2             |
    |        |-Trig------------A3             |
    +--------+                  |              |
                               |              |
     Servo                     |              |
    +-------+                  |              |
VCC-|       |-GND             |              |
    |       |-Signal----------D11            |
    +-------+                  |              |
                              |              |
     L298N                    |              |
    +--------+                |              |
    |        |-IN1------------D5             |
    |        |-IN2------------D4             |
    |        |-IN3------------D3             |
    |        |-IN4------------D2             |
    |   M1   |                |              |
    |   M2   |                |              |
    +--------+                +--------------+
        |
    External
    Power Supply
    (6-12V)
```

## Important Notes:
1. Make sure all GND connections are common between Arduino, L298N, and sensors
2. The L298N module needs an external power supply (6-12V) for the motors
3. ENA and ENB pins on L298N should be jumpered (set to high) if not connected to PWM pins
4. Double-check all connections before powering on
5. Mount the servo motor so it can rotate the ultrasonic sensor left and right
6. Ensure proper polarity when connecting the DC motors

## Power Supply Considerations:
- Arduino can be powered via USB while programming
- Motors should be powered by external power supply through L298N
- Don't connect external power supply directly to Arduino
- Make sure to connect the ground of power supply to Arduino ground

## Troubleshooting Tips:
1. If motors spin in wrong direction, swap the corresponding IN1/IN2 or IN3/IN4 connections
2. If servo movement is restricted, check for mechanical obstructions
3. If ultrasonic readings are inconsistent, check for loose connections
4. Ensure adequate power supply for both logic and motor circuits
