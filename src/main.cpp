#include <Arduino.h>
#include <display/displayManager.h>
#include <stepper/stepper.h>
#include <stepper/dispenser.h>
#include <cstdlib>
#include "buttons/buttonsManager.h"

ButtonsManager buttonsManager;
const int buttonPin = 27;

// The setup routine runs once when you press reset:
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  initDisplay();
  Serial.begin(9600);              

  // Initialize the digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  setupDispenser();
  buttonsManager.onLeftClick([]() {
    blink();
  });
}



void loop() {

  delay(2000);

  dispense();

  // if (digitalRead(buttonPin) == HIGH) { 
  //   // Check if button is pressed
  //   exit(0);
  // }

  renderDisplay();

  buttonsManager.checkButtons();
}



