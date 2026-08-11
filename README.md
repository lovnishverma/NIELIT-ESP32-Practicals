# NIELIT ESP32 Practicals

A structured Arduino library containing the complete **NIELIT ESP32 Practical Series (2.1–2.15)**.

The library provides classroom-ready ESP32 practical programs covering embedded systems, sensors, networking, IoT, MQTT, cloud integration, TinyML, ESP32-CAM, computer vision, and smart attendance systems.

---

## Features

- 15 complete ESP32 practical programs
- Direct access through the Arduino IDE **Examples** menu
- Designed for classroom and laboratory training
- ESP32 GPIO and hardware interfacing
- Wi-Fi and HTTP communication
- JSON and MQTT
- Firebase cloud integration
- Embedded Machine Learning / TinyML
- ESP32-CAM
- Face detection
- QR-based attendance
- Reusable NIELIT library utilities
- Compatible with Arduino IDE

---

# Installation

## Method 1 — Arduino Library Manager

This is the recommended installation method.

1. Open **Arduino IDE**.
2. Go to:

   **Tools → Manage Libraries**

3. Search for:

   ```text
   NIELIT ESP32 Practicals
````

4. Click **Install**.

After installation, open:

**File → Examples → NIELIT ESP32 Practicals**

and select the required practical.

---

## Method 2 — ZIP Installation

You can also install the library manually.

1. Download the library ZIP.

2. Open Arduino IDE.

3. Go to:

   **Sketch → Include Library → Add .ZIP Library...**

4. Select the ZIP file.

5. Restart Arduino IDE if necessary.

After installation:

**File → Examples → NIELIT ESP32 Practicals**

---

# Practical List

| Practical | Title                            |
| --------- | -------------------------------- |
| **2.1**   | Hardware Inputs / Outputs        |
| **2.2**   | Push Button and LED              |
| **2.3**   | I2C LCD                          |
| **2.4**   | DHT Sensor                       |
| **2.5**   | Timer / Weather Station          |
| **2.6**   | Wi-Fi Connectivity               |
| **2.7**   | ESP32 Web Server                 |
| **2.8**   | HTTP + JSON                      |
| **2.9**   | MQTT                             |
| **2.10**  | Industrial MQTT Telemetry        |
| **2.11**  | Firebase Cloud Telemetry         |
| **2.12**  | Embedded Machine Learning / Iris |
| **2.13**  | ESP32-CAM Web Server             |
| **2.14**  | Face Detection                   |
| **2.15**  | QR Attendance + Firebase         |

---

# Recommended Student Workflow

Students only need to install this library once.

### Step 1 — Install the ESP32 Board Package

Install the official ESP32 board package through the Arduino IDE's Boards Manager.

Select the ESP32 board appropriate for the hardware being used.

### Step 2 — Install NIELIT ESP32 Practicals

Use:

**Tools → Manage Libraries → Search → `NIELIT ESP32 Practicals` → Install**

### Step 3 — Install Practical Dependencies

Some practicals require additional libraries. Install them through:

**Tools → Manage Libraries**

### Step 4 — Open a Practical

Go to:

**File → Examples → NIELIT ESP32 Practicals**

Select the required practical.

### Step 5 — Configure

Change only configuration values marked with:

```cpp
YOUR_...
```

For example:

```cpp
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
```

### Step 6 — Select Board and Port

Select:

* Appropriate ESP32 board
* Correct COM/serial port

### Step 7 — Compile and Upload

Click **Verify** first and then **Upload**.

---

# Third-Party Dependencies

Some practicals require additional Arduino libraries.

Install the required dependencies through the Arduino IDE Library Manager.

| Practical | Required Dependencies                                     |
| --------- | --------------------------------------------------------- |
| **2.3**   | LiquidCrystal_I2C                                         |
| **2.4**   | DHT sensor library                                        |
| **2.5**   | LiquidCrystal_I2C, DHT sensor library                     |
| **2.8**   | ArduinoJson                                               |
| **2.9**   | PubSubClient                                              |
| **2.10**  | PubSubClient, ArduinoJson, DHT sensor library             |
| **2.11**  | ArduinoJson, DHT sensor library                           |
| **2.15**  | LiquidCrystal_I2C, ESP32QRCodeReader, Firebase ESP Client |

### ESP32-CAM

Practicals **2.13** and **2.14** use:

```cpp
#include "esp_camera.h"
```

The camera component is provided by the ESP32 Arduino core.

No separate `esp_camera` library should normally be installed.

---

# Wi-Fi Credentials

Never publish real Wi-Fi credentials in this repository.

Examples use placeholders such as:

```cpp
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
```

Replace these values with your local network credentials before uploading.

> **Security:** Never commit Wi-Fi passwords, Firebase credentials, API keys, MQTT credentials, tokens, or other private information to a public repository.

---

# Firebase Configuration

Practical **2.11** and **2.15** require Firebase configuration.

Students must configure their own Firebase project and credentials according to the instructions provided with the practical.

Do not use institutional or personal Firebase credentials in classroom-distributed source code.

---

# ESP32-CAM

Practicals **2.13** and **2.14** require an ESP32-CAM compatible board.

For an AI-Thinker ESP32-CAM:

1. Select the appropriate ESP32-CAM board configuration.
2. Connect the programming interface correctly.
3. Ensure adequate power.
4. Follow the practical-specific upload procedure.
5. Remove boot/programming connections as required before normal operation.

ESP32-CAM projects can require significantly more power than simple GPIO projects. Use an appropriate regulated power source.

---

# Library Usage

This project is primarily an **educational practical library**.

The practical programs are available directly through:

**File → Examples → NIELIT ESP32 Practicals**

The package also provides the following library header:

```cpp
#include <NIELIT_ESP32_Practicals.h>
```

The header provides the library version and course-related utility functionality.

Example:

```cpp
#include <NIELIT_ESP32_Practicals.h>

void setup() {
    Serial.begin(115200);

    Serial.println(NIELIT_ESP32_PRACTICALS_VERSION);
}

void loop() {
}
```

---

# Package Structure

```text
NIELIT_ESP32_Practicals/
│
├── library.properties
├── keywords.txt
├── README.md
├── LICENSE
│
├── src/
│   ├── NIELIT_ESP32_Practicals.h
│   └── NIELIT_ESP32_Practicals.cpp
│
├── examples/
│   ├── Practical_2_1/
│   ├── Practical_2_2/
│   ├── Practical_2_3/
│   ├── Practical_2_4/
│   ├── Practical_2_5/
│   ├── Practical_2_6/
│   ├── Practical_2_7/
│   ├── Practical_2_8/
│   ├── Practical_2_9/
│   ├── Practical_2_10/
│   ├── Practical_2_11/
│   ├── Practical_2_12/
│   ├── Practical_2_13/
│   ├── Practical_2_14/
│   └── Practical_2_15/
│
└── extras/
    ├── Practical_2_13_Camera/
    ├── Practical_2_14_Face_Detection/
    └── Practical_2_15_Dependencies/
```

---

# Hardware

The practical series may use different ESP32-compatible hardware, including:

* ESP32 development boards
* ESP32-WROOM
* ESP32 DevKit
* ESP32-CAM
* DHT sensors
* I2C LCD
* LEDs
* Push buttons
* Relays
* RFID readers
* Sensors and actuators
* Camera modules

Refer to the individual practical before assembling the circuit.

---

# Safety

Always verify the voltage and current requirements of each component before connecting it to an ESP32.

Important:

* ESP32 GPIO operates at **3.3V logic**.
* Do not apply 5V directly to an ESP32 GPIO.
* Use appropriate driver circuits for relays, motors, and high-current loads.
* Use external power supplies when required.
* Do not connect mains voltage directly to an ESP32.
* Ensure a common ground when using appropriate external supplies and signal interfaces.

---

# Troubleshooting

### Library does not appear in Examples

Restart Arduino IDE and check:

```text
File → Examples → NIELIT ESP32 Practicals
```

If installed through Library Manager, verify that the library appears under:

```text
Sketch → Include Library
```

### Compilation error for a dependency

Check the practical's dependency table and install the required library through:

```text
Tools → Manage Libraries
```

### ESP32 board not available

Install the ESP32 board package through:

```text
Tools → Board → Boards Manager
```

Then search for:

```text
esp32
```

and install the appropriate Espressif ESP32 platform.

### ESP32-CAM upload problems

Check:

* Board selection
* Boot/programming mode
* Serial adapter wiring
* Power supply
* TX/RX connections
* GPIO0 boot configuration

Follow the upload procedure specified for the particular ESP32-CAM board.

---

# Version

Current release:

```text
v1.0.0
```

---

# Educational Purpose

This library is intended for educational, laboratory, and training purposes.

It is designed to support practical learning in:

* Embedded Systems
* IoT
* ESP32 Programming
* Sensor Interfacing
* Wireless Communication
* Cloud Computing
* MQTT
* Embedded Machine Learning
* Computer Vision
* AIoT

---

# Author

**Lovnish Verma**

NIELIT / Embedded Systems & AI/IoT Training

---

# License

This project is distributed under the license included in the repository.

See:

```text
LICENSE
```
