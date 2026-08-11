#include <NIELIT_ESP32_Practicals.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 17
#define DHTTYPE DHT11      // Change to DHT22 if required

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//----------------------------------------------------
// Hardware Timer
//----------------------------------------------------
hw_timer_t *timer = NULL;

volatile bool newDataFlag = false;

//----------------------------------------------------
// Interrupt Service Routine
//----------------------------------------------------
void IRAM_ATTR onTimer()
{
    newDataFlag = true;
}

//----------------------------------------------------
void setup()
{
    Serial.begin(115200);

    Wire.begin(21,22);

    lcd.init();
    lcd.backlight();

    dht.begin();

    lcd.setCursor(0,0);
    lcd.print("Weather Station");
    lcd.setCursor(0,1);
    lcd.print("Initializing");
    delay(1500);
    lcd.clear();

    //------------------------------------------------
    // Timer Configuration
    //------------------------------------------------

    // Timer frequency = 1 MHz
    timer = timerBegin(1000000);

    // Attach ISR
    timerAttachInterrupt(timer, &onTimer);

    // Alarm every 2 seconds
    timerAlarm(timer, 2000000, true, 0);

    Serial.println("Localized Weather Station Started");
}

//----------------------------------------------------
void loop()
{
    //------------------------------------------------
    // Event occurs only every 2 seconds
    //------------------------------------------------
    if(newDataFlag)
    {
        newDataFlag = false;

        float humidity = dht.readHumidity();
        float temperature = dht.readTemperature();

        if(isnan(humidity) || isnan(temperature))
        {
            Serial.println("DHT Read Failed");

            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Sensor Error");

            return;
        }

        //------------------------------------------------
        // Heat Index
        //------------------------------------------------
        float heatIndex =
            dht.computeHeatIndex(
                temperature,
                humidity,
                false);     // Celsius

        //------------------------------------------------
        // Serial Output
        //------------------------------------------------

        Serial.println("-----------------------------");
        Serial.printf("Temperature : %.1f C\n",temperature);
        Serial.printf("Humidity    : %.1f %%\n",humidity);
        Serial.printf("Heat Index  : %.1f C\n",heatIndex);

        //------------------------------------------------
        // LCD Output
        //------------------------------------------------

        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("T:");
        lcd.print(temperature,1);
        lcd.write(byte(223));
        lcd.print("C ");

        lcd.print("H:");
        lcd.print(humidity,0);
        lcd.print("%");

        lcd.setCursor(0,1);
        lcd.print("Feels:");
        lcd.print(heatIndex,1);
        lcd.write(byte(223));
        lcd.print("C");
    }

    //------------------------------------------------
    // CPU is FREE here
    //------------------------------------------------

    // Future tasks:
    // Read buttons
    // WiFi
    // MQTT
    // Firebase
    // Buzzer
    // LEDs
}