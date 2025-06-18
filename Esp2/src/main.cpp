#include <Arduino.h>

#define MQ5_PIN 36       // Analog input for MQ-5 sensor
#define TRIGGER_PIN 14   // Connected to relay's NO output

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, INPUT);
  Serial.println("ESP2 MQ-5 Gas Sensor Monitor Started");
}

void loop() {
  int triggerState = digitalRead(TRIGGER_PIN);

  if (triggerState == HIGH) {
    int gasValue = analogRead(MQ5_PIN);
    Serial.print("🔥 Gas sensor active! MQ-5 reading: ");
    Serial.println(gasValue);
    
    // You can add gas level thresholds here
    if (gasValue > 2000) {
      Serial.println("⚠️ HIGH GAS LEVEL DETECTED!");
    } else if (gasValue > 1000) {
      Serial.println("⚡ Moderate gas level");
    } else {
      Serial.println("✅ Normal gas level");
    }
  } else {
    Serial.println("⏳ Waiting for relay activation (temp < 30°C)...");
  }

  delay(1000);
}