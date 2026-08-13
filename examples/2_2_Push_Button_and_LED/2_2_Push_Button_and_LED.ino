#include <NIELIT_ESP32_Practicals.h>

// set pin numbers:
const int buttonPin = 16;     // onboard  flash button
const int ledPin =  5;      // onboard LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  if ( digitalRead(buttonPin) ==HIGH) {
      if (buttonState ==1) buttonState =0;
      else buttonState =1;
      while(digitalRead(buttonPin) ==HIGH ) ;
  }
  

  if (buttonState == 1) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}