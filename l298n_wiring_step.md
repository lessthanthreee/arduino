# L298N to Sensor Shield Connection Diagram

```
[Sensor Shield V5]                [L298N Motor Driver]
                                 +-----------------+
5V Pin  ----------------→        |     +5V        |
GND Pin ----------------→        |     GND        |
                                |                 |
Pin 10  ----------------→        |     ENA        |
Pin 9   ----------------→        |     IN1        |
Pin 8   ----------------→        |     IN2        |
Pin 7   ----------------→        |     IN3        |
Pin 6   ----------------→        |     IN4        |
Pin 5   ----------------→        |     ENB        |
                                +-----------------+

Top View of L298N Motor Driver:
+--------------------------------+
|                                |
|  +12V  GND  +5V               |
|   O     O    O                |
|                               |
|  ENA  IN1  IN2  IN3  IN4 ENB |
|   O    O    O    O    O    O  |
|                               |
| OUT1 OUT2      OUT3 OUT4     |
|   O    O        O    O       |
|                               |
+--------------------------------+

Connection Steps:
1. Power Connections (First):
   - Find a 5V pin on Sensor Shield → Connect to L298N +5V
   - Find a GND pin on Sensor Shield → Connect to L298N GND

2. Control Connections (Second):
   - Sensor Shield Pin 10 → L298N ENA
   - Sensor Shield Pin 9  → L298N IN1
   - Sensor Shield Pin 8  → L298N IN2
   - Sensor Shield Pin 7  → L298N IN3
   - Sensor Shield Pin 6  → L298N IN4
   - Sensor Shield Pin 5  → L298N ENB

Note: Don't connect motors or external power (12V) yet!

Tips:
- Double-check all connections before powering on
- Make sure wires are firmly connected
- Use different colored wires if possible to avoid confusion
- Keep wires neat and organized```
