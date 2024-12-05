# HC-SR04 Ultrasonic Sensor Wiring Guide

## HC-SR04 Sensor Pins (looking at the front with the two "eyes")
```
    [Front of HC-SR04]
    ┌──────────────┐
    │ O         O  │  <- Ultrasonic sensors (eyes)
    │              │
    │ VCC TRIG ECHO GND │  <- Pins at the bottom
    └──────────────┘

```

## Connection Steps:

1. Find Pin 12 on Sensor Shield:
   - Look for the row marked "12"
   - You'll see three pins: [G V S]
   - Use the 'S' pin

2. Find Pin 11 on Sensor Shield:
   - Look for the row marked "11"
   - You'll see three pins: [G V S]
   - Use the 'S' pin

3. Connect the wires:
   ```
   HC-SR04 Pin    →    Sensor Shield Pin
   -----------------------------
   VCC (first)    →    Any 'V' pin
   TRIG (second)  →    Pin 12 'S'
   ECHO (third)   →    Pin 11 'S'
   GND (fourth)   →    Any 'G' pin
   ```

## Tips:
- The HC-SR04 has 4 pins in a row
- Count from left to right when looking at the front (side with the "eyes")
- Make sure connections are firm
- Double-check that VCC and GND are connected to the correct pins

Would you like me to help you connect them one by one?
