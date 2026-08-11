#include <NIELIT_ESP32_Practicals.h>

#include <DHT.h>

#define DHTPIN 17          // Change if your DATA wire is on another GPIO
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.println("DHT11 Test Started");
}

void loop() {
  delay(2000);  // DHT11 needs about 2 seconds between readings

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C");

  Serial.print("    Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}