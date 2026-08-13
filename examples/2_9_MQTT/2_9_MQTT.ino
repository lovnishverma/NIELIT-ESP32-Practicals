#include <NIELIT_ESP32_Practicals.h>

#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "nielit/esp32/led";

#define LED_PIN 5

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {

  String msg = "";

  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  Serial.print("Received: ");
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

    String clientId = "ESP32Client-" + String(random(10000));

    if (client.connect(clientId.c_str())) {

      Serial.println("Connected");

      client.subscribe(mqtt_topic);

      Serial.print("Subscribed to: ");
      Serial.println(mqtt_topic);

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

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}