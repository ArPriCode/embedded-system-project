# ESP32 Border Alert: Wiring Guide

**Unplug the USB cable before wiring.** Connect all GND wires first, then connect power and signal wires. ESP32 GPIO pins are not 5 V tolerant.

## Pin connections

| Sensor / part | Module pin | ESP32 pin / power |
|---|---|---|
| Ultrasonic sensor (HC-SR04) | VCC | VIN / 5V |
|  | GND | GND |
|  | TRIG | GPIO 5 |
|  | ECHO | GPIO 18, through a voltage divider |
| PIR motion sensor (e.g. HC-SR501) | VCC | VIN / 5V |
|  | GND | GND |
|  | OUT | GPIO 6 |

The ESP32 board's 5 V pin may be labeled `VIN`, `5V`, or `V5`. Check the label on your board.
These GPIO choices are intended for a typical ESP32-S3 development board and avoid its native USB pins. Board layouts differ; confirm the GPIO labels and availability on your specific board before wiring.
The standard HC-SR04 is a 5 V module. Use 5 V/VIN for VCC unless your exact sensor is documented as 3.3 V-compatible.

## Voltage divider for the ultrasonic ECHO

Use a divider on the HC-SR04 ECHO pin:

```text
HC-SR04 ECHO ----[ 1 kΩ ]----+---- ESP32 GPIO 18
                             |
                           [ 2 kΩ ]
                             |
                            GND
```

This reduces the HC-SR04's 5 V ECHO signal to about 3.3 V. **Never connect ECHO directly to an ESP32 GPIO.**

## Wiring order

1. Unplug the ESP32 from USB.
2. Connect ESP32 GND, ultrasonic GND, and PIR GND together on the breadboard.
3. Power the HC-SR04 from 5V/VIN; connect TRIG to GPIO 5.
4. Add the voltage divider to the HC-SR04 ECHO pin. Connect the divider midpoint to GPIO 18.
5. Connect the PIR sensor to VIN/5V and GND, and connect OUT to GPIO 6.
6. Check all connections before plugging the ESP32 into USB.

## Test the sketch

Upload `BorderSecurityESP32.ino` and open the Serial Monitor at 115200 baud. Allow the PIR sensor 30-60 seconds to stabilize.

This is an educational/demo prototype, not a real perimeter-security system.
