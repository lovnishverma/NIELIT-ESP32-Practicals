#include <NIELIT_ESP32_Practicals.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

void setup() {
  Serial.begin(115200);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.println(WiFi.localIP());

  // -----------------------------
  // JSON Serialization + POST
  // -----------------------------
  StaticJsonDocument<200> doc;

  doc["temperature"] = 28.5;
  doc["humidity"] = 65;
  doc["device"] = "ESP32";

  String jsonPayload;
  serializeJson(doc, jsonPayload);

  Serial.println("\nGenerated JSON:");
  Serial.println(jsonPayload);

  HTTPClient http;

  http.begin("https://httpbin.org/post");
  http.addHeader("Content-Type", "application/json");

  int postResponse = http.POST(jsonPayload);

  Serial.print("POST Response Code: ");
  Serial.println(postResponse);

  if (postResponse > 0) {
    String response = http.getString();
    Serial.println(response);
  }

  http.end();

  // -----------------------------
  // HTTP GET + JSON Parsing
  // -----------------------------
  http.begin("https://httpbin.org/json");

  int getResponse = http.GET();

  Serial.print("\nGET Response Code: ");
  Serial.println(getResponse);

  if (getResponse > 0) {

    String payload = http.getString();

    DynamicJsonDocument responseDoc(4096);

    DeserializationError error =
      deserializeJson(responseDoc, payload);

    if (!error) {

      const char* title =
        responseDoc["slideshow"]["title"];

      Serial.println("Parsed JSON Successfully");
      Serial.print("Title: ");
      Serial.println(title);

    } else {
      Serial.println("JSON Parsing Failed");
    }
  }

  http.end();
}

void loop() {
}