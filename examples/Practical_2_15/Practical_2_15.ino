#include <NIELIT_ESP32_Practicals.h>

#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32QRCodeReader.h>
#include <Firebase_ESP_Client.h>
#include <time.h>

// Firebase helper headers
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// =====================================================
//                    USER SETTINGS
// =====================================================

// Wi-Fi
#define WIFI_SSID       "YOUR_WIFI_SSID"
#define WIFI_PASSWORD   "YOUR_WIFI_PASSWORD"

// Firebase
#define API_KEY "YOUR_FIREBASE_API_KEY"
#define DATABASE_URL "https://YOUR_PROJECT-default-rtdb.firebaseio.com/"

// Firebase Authentication user
#define USER_EMAIL "YOUR_FIREBASE_USER_EMAIL"
#define USER_PASSWORD "YOUR_FIREBASE_USER_PASSWORD"

// =====================================================
//                     I2C LCD
// =====================================================

#define LCD_SDA 13
#define LCD_SCL 14

// Most I2C LCD backpacks use 0x27.
// Change to 0x3F if required.
LiquidCrystal_I2C lcd(0x27, 16, 2);

// =====================================================
//                    QR READER
// =====================================================

// AI Thinker ESP32-CAM
ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);

struct QRCodeData qrCodeData;

// =====================================================
//                     FIREBASE
// =====================================================

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool firebaseReady = false;

// =====================================================
//                      NTP TIME
// =====================================================

// India Standard Time = UTC + 5:30
const long GMT_OFFSET_SEC = 19800;
const int DAYLIGHT_OFFSET_SEC = 0;

const char *NTP_SERVER = "pool.ntp.org";

// =====================================================
//                DUPLICATE PROTECTION
// =====================================================

String lastScannedID = "";

unsigned long lastScanTime = 0;

// Ignore same QR for 10 seconds
const unsigned long DUPLICATE_TIMEOUT = 10000;

// =====================================================
//                    LCD FUNCTIONS
// =====================================================

void showLCD(String line1, String line2)
{
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(line1.substring(0, 16));

  lcd.setCursor(0, 1);
  lcd.print(line2.substring(0, 16));
}

// =====================================================
//                    CONNECT WIFI
// =====================================================

void connectWiFi()
{
  showLCD("Connecting WiFi", "Please wait...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");

  unsigned long startTime = millis();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");

    // Do not block forever
    if (millis() - startTime > 20000)
    {
      Serial.println();
      Serial.println("WiFi connection timeout.");

      showLCD("WiFi Failed", "Restart device");

      return;
    }
  }

  Serial.println();
  Serial.println("WiFi connected.");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  showLCD("WiFi Connected", WiFi.localIP().toString());

  delay(1500);
}

// =====================================================
//                   INITIALIZE TIME
// =====================================================

void initializeTime()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Cannot synchronize time: WiFi offline.");
    return;
  }

  configTime(
    GMT_OFFSET_SEC,
    DAYLIGHT_OFFSET_SEC,
    NTP_SERVER
  );

  Serial.print("Synchronizing time");

  struct tm timeinfo;

  int attempts = 0;

  while (!getLocalTime(&timeinfo) && attempts < 20)
  {
    Serial.print(".");
    delay(500);

    attempts++;
  }

  Serial.println();

  if (attempts >= 20)
  {
    Serial.println("NTP synchronization failed.");
  }
  else
  {
    Serial.println("Time synchronized.");
  }
}

// =====================================================
//                  GET DATE STRING
// =====================================================

String getDate()
{
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo))
  {
    return "UNKNOWN_DATE";
  }

  char buffer[11];

  strftime(
    buffer,
    sizeof(buffer),
    "%Y-%m-%d",
    &timeinfo
  );

  return String(buffer);
}

// =====================================================
//                  GET TIME STRING
// =====================================================

String getTimeString()
{
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo))
  {
    return "UNKNOWN_TIME";
  }

  char buffer[9];

  strftime(
    buffer,
    sizeof(buffer),
    "%H:%M:%S",
    &timeinfo
  );

  return String(buffer);
}

// =====================================================
//                GET FULL TIMESTAMP
// =====================================================

String getTimestamp()
{
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo))
  {
    return "TIME_NOT_AVAILABLE";
  }

  char buffer[25];

  strftime(
    buffer,
    sizeof(buffer),
    "%Y-%m-%d %H:%M:%S",
    &timeinfo
  );

  return String(buffer);
}

// =====================================================
//                INITIALIZE FIREBASE
// =====================================================

void initializeFirebase()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Firebase initialization skipped: WiFi offline.");
    return;
  }

  Serial.println("Initializing Firebase...");

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  config.token_status_callback = tokenStatusCallback;

  Firebase.reconnectWiFi(true);

  Firebase.begin(
    &config,
    &auth
  );

  Serial.println("Firebase initialization started.");
}

// =====================================================
//                CHECK VALID IDENTIFIER
// =====================================================

bool isValidIdentifier(const String &id)
{
  if (id.length() < 3)
  {
    return false;
  }

  /*
     Optional:

     Add your own institutional rules here.

     Examples:

     Student:
        STU001
        STU002

     Employee:
        EMP001

     Asset:
        ASSET001
  */

  return true;
}

// =====================================================
//                DUPLICATE SCAN CHECK
// =====================================================

bool isDuplicate(const String &id)
{
  if (
    id == lastScannedID &&
    millis() - lastScanTime < DUPLICATE_TIMEOUT
  )
  {
    return true;
  }

  return false;
}

// =====================================================
//               WRITE ATTENDANCE TO FIREBASE
// =====================================================

bool writeAttendance(const String &id)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Firebase write failed: WiFi offline.");
    return false;
  }

  if (!Firebase.ready())
  {
    Serial.println("Firebase not ready.");
    return false;
  }

  String date = getDate();
  String currentTime = getTimeString();
  String timestamp = getTimestamp();

  FirebaseJson json;

  json.set("id", id);
  json.set("date", date);
  json.set("time", currentTime);
  json.set("timestamp", timestamp);
  json.set("status", "PRESENT");
  json.set("device", "ESP32_CAM_01");

  /*
      Firebase structure:

      attendance_logs
           |
           +--- unique Firebase push ID
                  |
                  +--- id
                  +--- date
                  +--- time
                  +--- timestamp
                  +--- status
                  +--- device
  */

  Serial.println("Uploading attendance record...");

  if (
    Firebase.RTDB.pushJSON(
      &fbdo,
      "/attendance_logs",
      &json
    )
  )
  {
    Serial.println("Firebase write successful.");

    Serial.print("Record key: ");
    Serial.println(fbdo.pushName());

    return true;
  }

  Serial.println("Firebase write FAILED.");

  Serial.print("Reason: ");
  Serial.println(fbdo.errorReason());

  return false;
}

// =====================================================
//                     PROCESS QR
// =====================================================

void processQRCode(String id)
{
  id.trim();

  Serial.println();
  Serial.println("================================");
  Serial.println("QR CODE DETECTED");
  Serial.println("================================");

  Serial.print("Payload: ");
  Serial.println(id);

  // -----------------------------------------------
  // Validate
  // -----------------------------------------------

  if (!isValidIdentifier(id))
  {
    Serial.println("Invalid identifier.");

    showLCD(
      "Invalid QR",
      "Try Again"
    );

    delay(2000);

    showLCD(
      "Attendance Hub",
      "Scan QR..."
    );

    return;
  }

  // -----------------------------------------------
  // Duplicate protection
  // -----------------------------------------------

  if (isDuplicate(id))
  {
    Serial.println("Duplicate scan ignored.");

    showLCD(
      id,
      "Already Logged"
    );

    delay(1500);

    showLCD(
      "Attendance Hub",
      "Scan QR..."
    );

    return;
  }

  // -----------------------------------------------
  // Record scan locally
  // -----------------------------------------------

  lastScannedID = id;
  lastScanTime = millis();

  showLCD(
    id,
    "Processing..."
  );

  // -----------------------------------------------
  // Firebase upload
  // -----------------------------------------------

  bool uploaded = writeAttendance(id);

  if (uploaded)
  {
    Serial.println("Attendance registered.");

    showLCD(
      id,
      "Attendance OK"
    );
  }
  else
  {
    Serial.println("Attendance cloud upload failed.");

    showLCD(
      id,
      "Cloud Error"
    );
  }

  delay(2500);

  showLCD(
    "Attendance Hub",
    "Scan QR..."
  );
}

// =====================================================
//                         SETUP
// =====================================================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("======================================");
  Serial.println(" SMART ATTENDANCE & ASSET MANAGEMENT");
  Serial.println("======================================");

  // ---------------------------------------------------
  // I2C
  // ---------------------------------------------------

  Wire.begin(
    LCD_SDA,
    LCD_SCL
  );

  // ---------------------------------------------------
  // LCD
  // ---------------------------------------------------

  lcd.init();
  lcd.backlight();

  showLCD(
    "Smart Attendance",
    "Starting..."
  );

  delay(1500);

  // ---------------------------------------------------
  // WiFi
  // ---------------------------------------------------

  connectWiFi();

  // ---------------------------------------------------
  // NTP
  // ---------------------------------------------------

  initializeTime();

  // ---------------------------------------------------
  // Firebase
  // ---------------------------------------------------

  initializeFirebase();

  // ---------------------------------------------------
  // QR Camera
  // ---------------------------------------------------

  Serial.println("Initializing ESP32-CAM QR reader...");

  showLCD(
    "Camera Init",
    "Please wait..."
  );

  reader.setup();

  reader.beginOnCore(1);

  Serial.println("QR reader initialized.");

  showLCD(
    "Attendance Hub",
    "Scan QR..."
  );

  Serial.println();
  Serial.println("System ready.");
  Serial.println("Present a QR code to the camera.");
}

// =====================================================
//                          LOOP
// =====================================================

void loop()
{
  // Keep WiFi alive
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi disconnected.");

    WiFi.reconnect();

    delay(1000);
  }

  // Check QR reader queue
  if (reader.receiveQrCode(&qrCodeData, 100))
  {
    if (qrCodeData.valid)
    {
      String payload =
        String(
          reinterpret_cast<const char *>(
            qrCodeData.payload
          )
        );

      processQRCode(payload);
    }
    else
    {
      Serial.println("QR detected but payload could not be decoded.");
    }
  }

  delay(10);
}