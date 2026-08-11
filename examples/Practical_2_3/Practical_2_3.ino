#include <NIELIT_ESP32_Practicals.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Most Wokwi I2C LCDs use address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("ESP32 I2C LCD");

  lcd.setCursor(0, 1);
  lcd.print("NIELIT ROPAR");
}

void loop() {

}