# NIELIT ESP32 Practicals Library

A single Arduino ZIP package containing the ESP32 practical examples **2.1 to 2.15**.

## Installation

1. Open Arduino IDE.
2. Go to **Sketch -> Include Library -> Add .ZIP Library...**
3. Select this ZIP file.
4. Restart Arduino IDE if the examples do not immediately appear.
5. Open **File -> Examples -> NIELIT ESP32 Practicals**.

Students do **not** need to manually copy 15 folders.

## Important: this is an Examples Library

The Arduino library convention is used intentionally:

- `src/` contains the installable library.
- `examples/` contains the complete practical sketches.
- Installing one ZIP makes all practicals available from the Arduino **Examples** menu.
- Students can also write their own sketch and use:

```cpp
#include <NIELIT_ESP32_Practicals.h>
```

The helper header provides the library version and small course utilities.

## Third-party libraries

Install these separately through **Arduino IDE -> Library Manager** when required:

| Practical | Required library |
|---|---|
| 2.3 | LiquidCrystal_I2C |
| 2.4 | DHT sensor library |
| 2.5 | LiquidCrystal_I2C, DHT sensor library |
| 2.8 | ArduinoJson |
| 2.9 | PubSubClient |
| 2.10 | PubSubClient, ArduinoJson, DHT sensor library |
| 2.11 | ArduinoJson, DHT sensor library |
| 2.15 | LiquidCrystal_I2C, ESP32QRCodeReader, Firebase ESP Client |

The ESP32 camera examples (2.13 and 2.14) use the `esp_camera.h` component supplied by the ESP32 Arduino core.

## Wi-Fi credentials

For classroom distribution, the examples use placeholders:

```cpp
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
```

Replace them before uploading.

**Do not distribute real Wi-Fi passwords or Firebase credentials inside a public library ZIP.**

## Practical list

- 2.1 — Hardware Inputs / Outputs
- 2.2 — Push Button and LED
- 2.3 — I2C LCD
- 2.4 — DHT Sensor
- 2.5 — Timer / Weather Station
- 2.6 — Wi-Fi Connectivity
- 2.7 — ESP32 Web Server
- 2.8 — HTTP + JSON
- 2.9 — MQTT
- 2.10 — Industrial MQTT Telemetry
- 2.11 — Firebase Cloud Telemetry
- 2.12 — Embedded Machine Learning / Iris
- 2.13 — ESP32-CAM Web Server
- 2.14 — Face Detection
- 2.15 — QR Attendance + Firebase

## ESP32 board

Install the Espressif ESP32 board package in Arduino IDE and select the board appropriate to the hardware being used.

For AI-Thinker ESP32-CAM practicals, select the appropriate AI-Thinker ESP32-CAM board configuration and follow the practical-specific upload/power instructions.

## Recommended student workflow

1. Install this ZIP once.
2. Install the required dependency libraries.
3. Open the desired practical from **File -> Examples -> NIELIT ESP32 Practicals**.
4. Change only the configuration values marked `YOUR_...`.
5. Select the correct ESP32 board and COM port.
6. Upload and run.

## Package structure

```text
NIELIT_ESP32_Practicals/
├── library.properties
├── keywords.txt
├── README.md
├── src/
│   ├── NIELIT_ESP32_Practicals.h
│   └── NIELIT_ESP32_Practicals.cpp
├── examples/
│   ├── Practical_2_1/
   ...
│   └── Practical_2_15/
└── extras/
    ├── Practical_2_13_Camera/
    ├── Practical_2_14_Face_Detection/
    └── Practical_2_15_Dependencies/
```
