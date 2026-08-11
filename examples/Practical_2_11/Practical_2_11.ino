#include <NIELIT_ESP32_Practicals.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <DHT.h>
 
// ----------------------------------------------------
// DHT22 CONFIGURATION
// ----------------------------------------------------
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
 
// ----------------------------------------------------
// WIFI CONFIGURATION
// ----------------------------------------------------
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
 
// ----------------------------------------------------
// FIREBASE CONFIGURATION
// ----------------------------------------------------
// Replace this with YOUR Firebase Realtime Database URL.
// Example: https://your-project-default-rtdb.firebaseio.com
const char* FIREBASE_URL = "https://nielitiotdht-default-rtdb.firebaseio.com";
 
// ----------------------------------------------------
// TELEMETRY INTERVAL
// ----------------------------------------------------
const unsigned long UPLOAD_INTERVAL = 5000;
unsigned long previousUpload = 0;
 
// ----------------------------------------------------
// CONNECT TO WIFI
// ----------------------------------------------------
void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
 
// ----------------------------------------------------
// UPDATE LATEST SENSOR DATA
// ----------------------------------------------------
void updateLatestData(float temperature, float humidity) {
  WiFiClientSecure client;
  // For this educational Wokwi practical, certificate verification is disabled.
  // Production applications should perform proper TLS certificate validation.
  client.setInsecure();
 
  HTTPClient https;
  String url = String(FIREBASE_URL) + "/latest.json";
 
  StaticJsonDocument<256> document;
  document["temperature"] = temperature;
  document["humidity"] = humidity;
  document["device"] = "ESP32";
  document["source"] = "Wokwi";
 
  String jsonPayload;
  serializeJson(document, jsonPayload);
 
  Serial.println();
  Serial.println("Updating latest telemetry...");
  Serial.print("Payload: ");
  Serial.println(jsonPayload);
 
  if (!https.begin(client, url)) {
    Serial.println("Unable to initialize HTTPS connection.");
    return;
  }
 
  https.addHeader("Content-Type", "application/json");
 
  // PUT replaces /latest with the newest sensor state.
  int httpCode = https.PUT(jsonPayload);
 
  if (httpCode >= 200 && httpCode < 300) {
    Serial.print("Latest telemetry updated. HTTP ");
    Serial.println(httpCode);
  } else {
    Serial.print("Latest update failed. HTTP ");
    Serial.println(httpCode);
    Serial.println(https.errorToString(httpCode));
  }
 
  https.end();
}
 
// ----------------------------------------------------
// CREATE HISTORICAL LOG ENTRY
// ----------------------------------------------------
void createHistoricalLog(float temperature, float humidity) {
  WiFiClientSecure client;
  client.setInsecure();
 
  HTTPClient https;
  String url = String(FIREBASE_URL) + "/logs.json";
 
  StaticJsonDocument<256> document;
  document["temperature"] = temperature;
  document["humidity"] = humidity;
  document["device"] = "ESP32";
  document["source"] = "Wokwi";
  document["uptime_ms"] = millis();
 
  String jsonPayload;
  serializeJson(document, jsonPayload);
 
  Serial.println("Creating historical record...");
 
  if (!https.begin(client, url)) {
    Serial.println("Unable to initialize HTTPS connection.");
    return;
  }
 
  https.addHeader("Content-Type", "application/json");
 
  // POST creates a Firebase-generated unique child key under /logs.
  int httpCode = https.POST(jsonPayload);
 
  if (httpCode >= 200 && httpCode < 300) {
    Serial.print("Historical record created. HTTP ");
    Serial.println(httpCode);
 
    // Firebase returns the generated unique record ID.
    String response = https.getString();
    Serial.print("Firebase Response: ");
    Serial.println(response);
  } else {
    Serial.print("Historical logging failed. HTTP ");
    Serial.println(httpCode);
    Serial.println(https.errorToString(httpCode));
  }
 
  https.end();
}
 
// ----------------------------------------------------
// SETUP
// ----------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(1000);
 
  Serial.println();
  Serial.println("======================================");
  Serial.println(" NIELIT Cloud Telemetry Practical 2.11");
  Serial.println(" ESP32 + DHT22 + Firebase");
  Serial.println("======================================");
 
  dht.begin();
  connectWiFi();
}
 
// ----------------------------------------------------
// MAIN LOOP
// ----------------------------------------------------
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost.");
    connectWiFi();
  }
 
  if (millis() - previousUpload >= UPLOAD_INTERVAL) {
    previousUpload = millis();
 
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
 
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read DHT22 sensor.");
      return;
    }
 
    Serial.println();
    Serial.println("--------------------------------------");
    Serial.print("Temperature: ");
    Serial.print(temperature, 1);
    Serial.println(" degC");
    Serial.print("Humidity: ");
    Serial.print(humidity, 1);
    Serial.println(" %");
 
    // 1. Update current/latest state.
    updateLatestData(temperature, humidity);
 
    // 2. Create historical telemetry entry.
    createHistoricalLog(temperature, humidity);
 
    Serial.println("Cloud synchronization complete.");
    Serial.println("--------------------------------------");
  }
}
