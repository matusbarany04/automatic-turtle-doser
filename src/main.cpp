#include <Arduino.h>
#include <display/displayManager.h>
#include <stepper/stepper.h>
#include <stepper/dispenser.h>
#include <cstdlib>
#include "buttons/buttonsManager.h"

ButtonsManager buttonsManager;
const int buttonPin = 27;
int menuIndex = 0;
int menuItems = 2;

void incrementMenuIndex() {
    menuIndex++; 
    if (menuIndex > menuItems) menuIndex = 0;
}

void decrementMenuIndex() {
    menuIndex--;
    if(menuIndex < 0) menuIndex = 0;
}


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
    invertButtonArea(0);
    delay(1000);
    decrementMenuIndex();
  });

   buttonsManager.onMiddleClick([]() {
    invertButtonArea(1);
    delay(1000);

  });

   buttonsManager.onRightClick([]() {
    invertButtonArea(2);
    delay(1000);
    incrementMenuIndex();

  });
}



void loop() {
  renderDisplay();
  drawSelectedIndicator(menuIndex * 8);
  buttonsManager.checkButtons();

  delay(500);

  dispense();

  // if (digitalRead(buttonPin) == HIGH) { 
  //   // Check if button is pressed
  //   exit(0);
  // }
  
  endRenderDisplay();
}




// this menu contains following items, time, dispense, 
void startMenu(){


  switch (menuIndex)
  {  
    case 0:
      // its the items 
      /* code */
      break;
    
    case 1:
      // its the dispense function 
      dispense(); 
      /* code */
      break;
    
    default:
      break;
  }
    

}



