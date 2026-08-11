#include <NIELIT_ESP32_Practicals.h>

#define BUTTON1 16
#define BUTTON2 4

#define LED1 5
#define LED2 18

#define BUZZER 32   // GPIO34 cannot be used as an output

bool led1State = LOW;
bool led2State = LOW;

bool lastBtn1 = HIGH;
bool lastBtn2 = HIGH;

void beep() {
  digitalWrite(BUZZER, HIGH);
  delay(80);
  digitalWrite(BUZZER, LOW);
}

void setup() {
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(BUZZER, LOW);
}

void loop() {
  bool btn1 = digitalRead(BUTTON1);
  bool btn2 = digitalRead(BUTTON2);

  // Button 1 pressed
  if (lastBtn1 == HIGH && btn1 == LOW) {
    led1State = !led1State;
    digitalWrite(LED1, led1State);
    beep();
    delay(50); // debounce
  }

  // Button 2 pressed
  if (lastBtn2 == HIGH && btn2 == LOW) {
    led2State = !led2State;
    digitalWrite(LED2, led2State);
    beep();
    delay(50); // debounce
  }

  lastBtn1 = btn1;
  lastBtn2 = btn2;
}