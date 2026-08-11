#include <NIELIT_ESP32_Practicals.h>

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

#define DHTPIN 17
#define DHTTYPE DHT11
#define LED_PIN 5

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* telemetryTopic = "nielit/factory/telemetry";
const char* controlTopic   = "nielit/factory/control";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastPublish = 0;

void callback(char* topic, byte* payload, unsigned int length) {

  String msg;

  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  Serial.print("Control Message: ");
  Serial.println(msg);

  if (msg == "1") {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON");
  }

  if (msg == "0") {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED OFF");
  }
}

void reconnect() {

  while (!client.connected()) {

    Serial.print("Connecting MQTT...");

    String clientId = "ESP32-" + String(random(10000));

    if (client.connect(clientId.c_str())) {

      Serial.println("Connected");

      client.subscribe(controlTopic);

    } else {

      Serial.print("Failed, rc=");
      Serial.println(client.state());

      delay(2000);
    }
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  if (millis() - lastPublish > 5000) {

    lastPublish = millis();

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    StaticJsonDocument<200> doc;

    doc["temperature"] = temperature;
    doc["humidity"] = humidity;
    doc["device"] = "ESP32";

    String payload;
    serializeJson(doc, payload);

    Serial.println(payload);

    client.publish(telemetryTopic, payload.c_str());
  }
}