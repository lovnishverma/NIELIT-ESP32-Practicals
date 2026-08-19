# NIELIT ESP32 Practicals

A structured Arduino library containing the complete **NIELIT ESP32 Practical Series (2.1–2.15)**.

The library provides classroom-ready ESP32 practical programs covering embedded systems, sensors, networking, IoT, MQTT, cloud integration, TinyML, ESP32-CAM, computer vision, and smart attendance systems.


<img width="940" height="788" alt="NIELIT ESP32 Practicals" src="https://github.com/user-attachments/assets/9ebb6c80-e96b-47f5-934b-e2df223783e4" />


---

<img width="718" height="578" alt="Screenshot" src="https://github.com/user-attachments/assets/6559659d-4243-4ca1-8a12-486dbb635584" />



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
```

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


| Practical | Simulation Link(s) |
|---|---|
| 2.1 Local Hardware I/O Integration — LED Array Control | https://wokwi.com/projects/466868959177654273<br>https://wokwi.com/projects/466892874137419777 |
| 2.2 Interrupt-Driven Hardware Inputs & Software Debouncing | https://wokwi.com/projects/470337342911561729<br>https://wokwi.com/projects/466919377125265409<br>https://wokwi.com/projects/466875285561787393 |
| 2.3 Bus Topologies — Interfacing an I2C LCD | https://wokwi.com/projects/466875970889181185<br>https://wokwi.com/projects/466919917516327937 |
| 2.4 Environmental Telemetry — Interfacing Digital DHT Sensors | https://wokwi.com/projects/471053320556576769<br>https://wokwi.com/projects/466920367250622465<br>https://wokwi.com/projects/466895389976744961 |
| 2.5 Intermediate Capstone — Independent Localized Weather Station | https://wokwi.com/projects/470350455832728577<br>https://wokwi.com/projects/466921948977586177<br>https://wokwi.com/projects/466922878062177281 |
| 2.6 Network Layer Operations — Access Point Authentication & IP Allocation | https://wokwi.com/projects/466955423742893057 |
| 2.7 Local Host Operations — Designing an Interactive Web Server | https://wokwi.com/projects/466957884087597057 |
| 2.8 REST API Client Architecture — Serialization and Parsing of JSON Payloads | https://wokwi.com/projects/466959130363466753 |
| 2.9 Machine-to-Machine (M2M) Telemetry — Implementing the MQTT Protocol | https://wokwi.com/projects/466973992521757697 |
| 2.10 Macro System Capstone — Enterprise Industrial Automation Node | https://wokwi.com/projects/467049761386592257 |
| 2.11 Cloud Persistence Architectures — Integrating Google Firebase Databases | https://wokwi.com/projects/470181664079028225 |
| 2.12 Embedded Machine Learning — Inline Iris Data Flower Classification | https://wokwi.com/projects/470184390324461569 |
| 2.13 Visual Data Acquisitions — Interfacing the ESP32 Camera Subsystem | *(no simulation link — requires physical ESP32-CAM)* |
| 2.14 Edge Computer Vision — Localized Human Facial Detection | *(no simulation link — requires physical ESP32-CAM)* |
| 2.15 Category Capstone — Automated Smart Attendance & Asset Management Hub | *(no simulation link — requires physical hardware)* |


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
│   ├── 2_1_Hardware_Inputs_Outputs/
│   ├── 2_2_Push_Button_and_LED/
│   ├── 2_3_I2C_LCD/
│   ├── 2_4_DHT_Sensor/
│   ├── 2_5_Timer_Weather_Station/
│   ├── 2_6_Wi_Fi_Connectivity/
│   ├── 2_7_ESP32_Web_Server/
│   ├── 2_8_HTTP_JSON/
│   ├── 2_9_MQTT/
│   ├── 2_10_Industrial_MQTT_Telemetry/
│   ├── 2_11_Firebase_Cloud_Telemetry/
│   ├── 2_12_Embedded_Machine_Learning_Iris/
│   ├── 2_13_ESP32_CAM_Web_Server/
│   ├── 2_14_Face_Detection/
│   └── 2_15_QR_Attendance_Firebase/
│
└── extras/
    ├── 2_14_Face_Detection/
    └── 2_15_Dependencies/
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
v1.0.3
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

# Authors

**Dr. Sarwan Singh**, **Lovnish Verma**

NIELIT / Embedded Systems & AI/IoT Training

---

# License

This project is distributed under the license included in the repository.

See:

```text
MIT LICENSE
```
