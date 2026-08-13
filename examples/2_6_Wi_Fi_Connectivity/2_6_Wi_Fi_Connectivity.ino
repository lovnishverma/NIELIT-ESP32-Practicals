#include <NIELIT_ESP32_Practicals.h>

#include <WiFi.h>

// Wi-Fi access point
const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";
void setup()
{
    // Initialize standard serial connection for stream auditing
    Serial.begin(115200);
    delay(10);

    Serial.println();
    Serial.println("Network Layer Operations");
    Serial.print("Connecting to Access Point: ");
    Serial.println(ssid);

    // Set ESP32 to Station Mode (client)
    WiFi.mode(WIFI_STA);

    // Initiate connection
    WiFi.begin(ssid, password);

    // Wait for connection to establish
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    // Connection successful
    Serial.println("");
    Serial.println("Wi-Fi Connected successfully!");
    // Retrieve and print the dynamic IP allocated by the DHCP server
    Serial.print("Allocated IP Address: ");
    Serial.println(WiFi.localIP());
}
void loop()
{    // Nothing to do here for this specific initialization task
    delay(1000);
}
