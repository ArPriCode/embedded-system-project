# ESP32 Border Security Sensor Prototype

This is a simple sensor-monitoring prototype, not an AI system. It raises an alert when the ultrasonic sensor sees an object within 200 cm or the PIR sensor detects motion.

## Parts assumed

- ESP32-S3 development board
- 1 HC-SR04 ultrasonic module
- 1 PIR motion sensor (such as HC-SR501)
- 1 x 1 kΩ resistor and 1 x 2 kΩ resistor for the ultrasonic Echo voltage divider

## Wiring

Connect all grounds together. Power the ESP32-S3 from USB. A standard HC-SR04 normally needs 5 V; use the board's 5V/VIN pin for the sensor unless your exact model is documented for 3.3 V operation.

| Module pin | ESP32 connection |
| --- | --- |
| Ultrasonic VCC / GND | 5V (VIN) / GND |
| Ultrasonic TRIG / ECHO | GPIO 5 / GPIO 18 through a voltage divider |
| PIR sensor VCC / GND / OUT | 5V (VIN) / GND / GPIO 6 |

These GPIO choices are intended for a typical ESP32-S3 development board. Check your specific board's pin labels and wiring diagram before connecting.

### Important: ultrasonic Echo voltage

HC-SR04 Echo is typically 5 V, while ESP32 GPIO pins are **not 5 V tolerant**. Do not connect Echo directly to the ESP32. Wire:

```text
HC-SR04 ECHO ---- 1 kΩ ----+---- ESP32 GPIO 18
                           |
                          2 kΩ
                           |
                          GND
```

The divider reduces the 5 V Echo signal to about 3.3 V. Use a common ground.

## Upload and test

1. Open `BorderSecurityESP32.ino` in Arduino IDE.
2. Install/select the ESP32 board support, then choose the ESP32S3 Dev Module and its USB port.
3. Upload and open Serial Monitor at **115200 baud**.
4. Allow the PIR sensor about 30-60 seconds to stabilize. Test each sensor individually.

## Browser monitoring dashboard

The project includes `monitor.html`, a live dashboard that reads sensor telemetry from the ESP32 over USB serial.

1. Upload the updated `BorderSecurityESP32.ino` sketch.
2. Close Arduino IDE's Serial Monitor; only one application can use the ESP32 serial port at a time.
3. In a terminal opened in this project folder, run `python3 -m http.server 8001`.
4. Open `http://localhost:8001/monitor.html` in Chrome or Edge.
5. Select **Connect ESP32** and choose the ESP32 serial port.

The dashboard uses the Web Serial API, which is supported in Chrome and Edge on desktop. Keep the terminal running while using the dashboard. Stop the local server with Ctrl+C when finished.

The alert distance can be adjusted with `ALERT_DISTANCE_CM`.

The ESP32 USB supplies the board. Never feed 5 V directly into an ESP32 GPIO; use the ECHO voltage divider shown above.
