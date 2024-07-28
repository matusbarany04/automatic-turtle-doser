#include <Arduino.h>
#include <display/displayManager.h>
#include <stepper/stepper.h>
#include <stepper/dispenser.h>
#include <cstdlib>
#include "buttons/buttonsManager.h"

ButtonsManager buttonsManager;
const int buttonPin = 27;
const int BACKLIGHT_PIN = 5;
bool backlight = true;

int menuIndex = 0;
int menuItems = 2;

unsigned long timeNow = 0;


const int MAIN_MENU = 0;
const int TIME_MENU = 1;
const int CHANGE_CURRENT_TIME_SCREEN = 3;
const int CHANGE_DISPENSE_TIME_SCREEN = 4;
int currentMenu = MAIN_MENU;


void backlightOn() {
  digitalWrite(BACKLIGHT_PIN, LOW);
  backlight = true;
}

void backlightOff() {
  digitalWrite(BACKLIGHT_PIN, HIGH);
  backlight = false;

}

void incrementMenuIndex() {
    menuIndex++; 
    if (menuIndex > menuItems) menuIndex = 0;
}

void decrementMenuIndex() {
    menuIndex--;
    if(menuIndex < 0) menuIndex = 0;
}

void changeMenu(int menuIndex){
  currentMenu = menuIndex;
  menuIndex = 0;
  if(currentMenu == TIME_MENU){
    setDescription(" back\n time now\n dispense time");
    menuItems = 2;
  }
  else if (currentMenu == CHANGE_CURRENT_TIME_SCREEN){
    setDescription("time now");
    menuItems = 0;
  }
  else if (currentMenu == CHANGE_DISPENSE_TIME_SCREEN){
    setDescription(" dispense time");
    menuItems = 0;

  }else if (currentMenu == MAIN_MENU)
  {
    menuItems = 2;
    resetDescription();
  }
  
}

void timeMenu(){
  switch (menuIndex)
  {
  case 0: //back
    changeMenu(MAIN_MENU);
    resetDescription();
    break;
  case 1: // time now 
    changeMenu(CHANGE_CURRENT_TIME_SCREEN);
    break;
  case 2: // dispense time
    changeMenu(CHANGE_DISPENSE_TIME_SCREEN);
    break;
  default:
    break;
  }
}



// this menu contains following items, time, dispense, 
void startMenu(){


  switch (menuIndex)
  {  
    case 0:

      changeMenu(TIME_MENU);
      
      break;
    
    case 1:
      // its the dispense function 
      dispense(); 
      /* code */
      break;
    case 2:
      // it is the backlight option
      if(backlight){
        backlightOff();
      }
      else{
        backlightOn();
      }

      break;
    default:
      break;
  }
    

}

void dispenseTimeMenu(){
  changeMenu(TIME_MENU);
}

void currentTimeMenu(){
  timeNow = menuIndex;
  changeMenu(TIME_MENU);
}

void  runMenu(){
  switch (currentMenu)
  {
    case MAIN_MENU:
      startMenu();
      break;

    case TIME_MENU:
      timeMenu();
      break;
  
    case CHANGE_CURRENT_TIME_SCREEN:
      currentTimeMenu();
      break;

    case CHANGE_DISPENSE_TIME_SCREEN:
      dispenseTimeMenu();
      break;
    
    default:
      break;
  }
}


// The setup routine runs once when you press reset:
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  initDisplay();
  Serial.begin(9600); 
  pinMode(BACKLIGHT_PIN, OUTPUT);
  if(backlight){
    backlightOn();
  } else{
    backlightOff();
  }

  // Initialize the digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  setupDispenser();
  buttonsManager.onLeftClick([]() {
    invertButtonArea(0);
    delay(200);
    decrementMenuIndex();
  });

   buttonsManager.onMiddleClick([]() {
    invertButtonArea(1);
    delay(200);
    // figure out which menu we are on 
    runMenu();
  });

   buttonsManager.onRightClick([]() {
    invertButtonArea(2);
    delay(200);
    incrementMenuIndex();

  });
}





void loop() {
  renderDisplay();
  drawSelectedIndicator(menuIndex * 8);
  buttonsManager.checkButtons();


  endRenderDisplay();
}


