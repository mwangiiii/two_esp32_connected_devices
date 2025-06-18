#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 15        // DHT22 Signal pin
#define DHTTYPE DHT22
#define RELAY_PIN 4      // Relay IN pin

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("ESP1 DHT22 Temperature Monitor Started");
  
  // Initialize DHT sensor
  dht.begin();
  
  // Initialize relay pin
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Start with relay OFF
  
  // Give DHT sensor time to stabilize
  delay(2000);
  Serial.println("DHT22 sensor initialized");
}

void loop() {
  Serial.println("Reading DHT22 sensor...");
  
  // Read temperature and humidity
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Check if readings are valid
  if (isnan(temp) || isnan(hum)) {
    Serial.println("❌ Failed to read from DHT sensor!");
    Serial.println("   Check wiring and sensor connection");
    delay(3000); // Wait longer before retry
    return;
  }

  // Display readings
  Serial.print("🌡️ Temperature: ");
  Serial.print(temp);
  Serial.print("°C, 💧 Humidity: ");
  Serial.print(hum);
  Serial.println("%");

  // Control relay based on temperature
  if (temp > 25.0) { // Lowered threshold for testing
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("🚨 Relay ON (Temperature > 25°C)");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("✅ Relay OFF (Temperature <= 25°C)");
  }
  
  delay(2000); // Wait 2 seconds between readings
}