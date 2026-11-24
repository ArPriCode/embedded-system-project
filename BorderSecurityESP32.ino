/*
  ESP32-S3 sensor monitor
  Sensors: 1 HC-SR04 ultrasonic, 1 PIR motion sensor
*/

constexpr int TRIG_PIN = 5;
constexpr int ECHO_PIN = 18;
constexpr int PIR_PIN = 6;

constexpr float ALERT_DISTANCE_CM = 200.0F;
constexpr unsigned long ECHO_TIMEOUT_US = 30000UL;
constexpr unsigned long REPORT_INTERVAL_MS = 500UL;

unsigned long lastReportMs = 0;

float measureDistanceCm(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(3);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  const unsigned long durationUs = pulseIn(echoPin, HIGH, ECHO_TIMEOUT_US);
  if (durationUs == 0) {
    return -1.0F;
  }
  return durationUs * 0.0343F / 2.0F;
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  Serial.println("ESP32-S3 sensor monitor started.");
  Serial.println("PIR sensor may need 30-60 seconds to stabilize.");
}

void loop() {
  const float distanceCm = measureDistanceCm(TRIG_PIN, ECHO_PIN);

  const bool motionDetected = digitalRead(PIR_PIN) == HIGH;
  const bool objectNearby = distanceCm >= 2.0F && distanceCm <= ALERT_DISTANCE_CM;
  const bool alert = motionDetected || objectNearby;

  const unsigned long now = millis();
  if (now - lastReportMs >= REPORT_INTERVAL_MS) {
    lastReportMs = now;
    Serial.print(F("{\"distance_cm\":"));
    if (distanceCm < 0.0F) {
      Serial.print(F("null"));
    } else {
      Serial.print(distanceCm, 1);
    }
    Serial.print(F(",\"pir\":"));
    Serial.print(motionDetected ? F("true") : F("false"));
    Serial.print(F(",\"alert\":"));
    Serial.println(alert ? F("true}") : F("false}"));
  }
}
