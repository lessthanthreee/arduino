# Sensor Shield V5 Pin Layout

```
[TOP VIEW OF SENSOR SHIELD V5]

USB Port Side
+------------------------------------------+
|                                          |
|  Analog Pins                Digital Pins  |
|  A0 [G V S]                [G V S] D0    |
|  A1 [G V S]                [G V S] D1    |
|  A2 [G V S]                [G V S] D2    |
|  A3 [G V S]                [G V S] D3    |
|  A4 [G V S]                [G V S] D4    |
|  A5 [G V S]                [G V S] D5    |
|                            [G V S] D6    |
|                            [G V S] D7    |
|                            [G V S] D8    |
|                            [G V S] D9    |
|                            [G V S] D10   |
|                            [G V S] D11   |
|                            [G V S] D12   |
|                            [G V S] D13   |
+------------------------------------------+

G = GND (Ground)
V = VCC (5V Power)
S = Signal (Digital/Analog Pin)

The pins we need (D5-D10) are on the right side:
- D5  (Pin 5)  → ENB on L298N
- D6  (Pin 6)  → IN4 on L298N
- D7  (Pin 7)  → IN3 on L298N
- D8  (Pin 8)  → IN2 on L298N
- D9  (Pin 9)  → IN1 on L298N
- D10 (Pin 10) → ENA on L298N

For each digital pin (D5-D10), you'll see three pins in a row:
[G V S] where:
- G is Ground
- V is 5V power
- S is the Signal pin (this is the one we use for control)
```

For the L298N connections:
1. Use any "V" pin for the 5V connection to L298N
2. Use any "G" pin for the GND connection to L298N
3. For the control pins (ENA, IN1, IN2, etc), use the "S" pins from D5-D10

Would you like me to help you identify specific pins to connect first?
