#include <Arduino.h>
#include <display/displayManager.h>
#include <stepper/stepper.h>
#include <stepper/dispenser.h>
#include <cstdlib>
#include <stdlib.h>
#include "buttons/buttonsManager.h"
#include "files/SettingsManager.h"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include <stdio.h>
#include <math.h>

ButtonsManager buttonsManager;
const int buttonPin = 27;
const int BACKLIGHT_PIN = 5;
bool backlight = true;
bool dispensed = false;

int menuIndex = 0;
int menuItems = 3;
const int TIME_STEP = 15;

unsigned long timeNow = 0;
unsigned long dispenseTime = 18 * 60;

const int MAIN_MENU = 0;
const int TIME_MENU = 1;
const int CHANGE_CURRENT_TIME_SCREEN = 3;
const int CHANGE_DISPENSE_TIME_SCREEN = 4;
const int MOTOR_CONF_MENU = 5;
const int DEBUG_MENU = 6;
int currentMenu = DEBUG_MENU;

int currentTimeOffset = 15 * 60 ;
int absoluteTime = 0;

#define FLASH_TARGET_OFFSET (256 * 1024)

const uint8_t *flash_target_contents = (const uint8_t *)(XIP_BASE + FLASH_TARGET_OFFSET);

#define DATA_SIZE (sizeof(int) * 2 + sizeof(bool))  // Total size needed to store two ints and one bool
#define FLASH_PAGE_SIZE (256)  // Flash page size
#define FLASH_SECTOR_SIZE (4096)  // Flash sector size


// Function to get the current time in minutes since the program started
int getAbsoluteTimeInMinutes() {
    absolute_time_t now = get_absolute_time();
    int64_t now_us = to_us_since_boot(now); /// TIME_STEP;

    return (now_us / 60000000); // % (24 * 60 / TIME_STEP); // Convert microseconds to minutes, modulo them to repeat
}
int updateCurrentTime(){
  absoluteTime =  getAbsoluteTimeInMinutes();
  
  timeNow = (absoluteTime + currentTimeOffset) % (24 * 60);
  return timeNow;
}


// Define data structure for storage

void print_buf(const uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        Serial.print(buf[i], HEX);
        if (i % 16 == 15)
            Serial.println();
        else
            Serial.print(" ");
    }
}


void write_data_to_flash(const uint8_t* data, size_t size) {
    Serial.println("Starting flash write...");

    // Ensure size is correctly aligned
    if (FLASH_TARGET_OFFSET % FLASH_PAGE_SIZE != 0 || size % FLASH_PAGE_SIZE != 0) {
        Serial.println("Error: Offset or size is not aligned to page size.");
        return;
    }

    // Disable interrupts
    uint32_t ints = save_and_disable_interrupts();

    // Erase the flash sector
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    Serial.println("Flash sector erased.");

    // Write the data to the flash
    flash_range_program(FLASH_TARGET_OFFSET, data, size);
    Serial.println("Flash written.");

    // Restore interrupts
    restore_interrupts(ints);

    Serial.println("Flash write complete.");
}

void read_data_from_flash(uint8_t* data, size_t size) {
    Serial.println("Reading data from flash...");

    
    // Read the data from flash
    memcpy(data, flash_target_contents, size);

    Serial.println("Data read from flash:");
    print_buf(data, size);
}

String minutesToTimeString(int minutes) {
    int hours = minutes / 60;
    int mins = minutes % 60;
    char timeString[6]; // "HH:MM" + null terminator
    snprintf(timeString, sizeof(timeString), "%02d:%02d", hours, mins);
    return String(timeString);
}
int timeStringToMinutes(String timeString) {
    int hours = timeString.substring(0, 2).toInt();
    int mins = timeString.substring(3, 5).toInt();
    return (hours * 60) + mins;
}

void backlightOn() {
  digitalWrite(BACKLIGHT_PIN, LOW);
  backlight = true;
}

void backlightOff() {
  digitalWrite(BACKLIGHT_PIN, HIGH);
  backlight = false;

}

void updateCurrentTimeMenu(){
    setDescription(minutesToTimeString(menuIndex)); 
}

void updateDispenseTimeMenu(){
    setDescription(minutesToTimeString(menuIndex)); 
}

void incrementMenuIndex() {
    menuIndex++; 
    if (menuIndex > menuItems) menuIndex = 0;

    if(currentMenu == CHANGE_CURRENT_TIME_SCREEN){
      updateCurrentTimeMenu();
    }
    if (currentMenu == CHANGE_DISPENSE_TIME_SCREEN)
    {
      updateDispenseTimeMenu();
    }
    
}

void decrementMenuIndex() {
    menuIndex--;
    if(menuIndex < 0) menuIndex = 0;
    
    if(currentMenu == CHANGE_CURRENT_TIME_SCREEN){
      updateCurrentTimeMenu();
    }

    if (currentMenu == CHANGE_DISPENSE_TIME_SCREEN)
    {
      updateDispenseTimeMenu();
    }
}

void changeMenu(int menu){
  currentMenu = menu;
  menuIndex = 0;
  if(currentMenu == TIME_MENU){
    setDescription(" spat\n cas teraz\n cas jedlo\n debug");
    menuItems =  3;
  }
  else if (currentMenu == CHANGE_CURRENT_TIME_SCREEN){
    menuItems = (60 * 24); /// TIME_STEP;
    menuIndex = timeNow;
    setDescription(minutesToTimeString(menuIndex)); // * TIME_STEP
  }
  else if (currentMenu == CHANGE_DISPENSE_TIME_SCREEN){
    menuIndex =  dispenseTime;
    menuItems = (60 * 24) ;
    setDescription(minutesToTimeString(menuIndex)); // * TIME_STEP

  }else if (currentMenu == MAIN_MENU)
  {
    menuItems = 3;
    resetDescription();
  }else if(currentMenu == MOTOR_CONF_MENU){
    setDescription(" spat\n Start\n Stop");
    menuItems = 2;
  }else if (currentMenu == DEBUG_MENU){
    setDescription(" spat");
    menuItems = 0;
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
  case 3: // dispense time
    changeMenu(DEBUG_MENU);
    break;
  default:
    break;
  }
}
void motorMenu(){
  
  switch (menuIndex)
  {  
    case 0:
      changeMenu(MAIN_MENU);
      break;
    case 1:
      startConfiguration();
      break;
    case 2:
      stopConfiguration();
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
    case 3: // motor conf
      changeMenu(MOTOR_CONF_MENU);
      break;
    default:
      break;
  }
    

}

void dispenseTimeMenu(){
  dispenseTime = menuIndex;
  changeMenu(TIME_MENU);
}

void currentTimeMenu(){
  Serial.println(menuIndex);
  Serial.println(timeNow);
  
  currentTimeOffset += menuIndex - timeNow;

  changeMenu(TIME_MENU);
}

void debugMenu(){
  changeMenu(TIME_MENU);
}

void debugUpdate(){
  
  int timeNows = updateCurrentTime();
  Serial.println(timeNows);

  char description[15]; 
  // sprintf(description, "spat \n %d:%d", 
  // (timeNows * 15 / 60), 
  // (timeNows * 15 - (timeNows * 15 / 60) * 60));
  sprintf(description,"spat \n %d", timeNows);

  setDescription(description);
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
    case MOTOR_CONF_MENU:
      motorMenu();
      break;
    case DEBUG_MENU:
      debugMenu();
      break;
    default:
      break;
  }
}

// SettingsManager settingsManager
void setup() {


  pinMode(buttonPin, INPUT_PULLUP);
  initDisplay();

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
    delay(100);
    decrementMenuIndex();
  });

  buttonsManager.onLeftHold([](int duration) {
    invertButtonArea(0);
    delay(max(50 - 20 * log10(duration), 0));
    if(duration > 1000){
      decrementMenuIndex();
    }
    if(duration > 5000){
      decrementMenuIndex();
      decrementMenuIndex();
      decrementMenuIndex();
    }
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
    delay(100);
    incrementMenuIndex();

  });

   buttonsManager.onRightHold([](int duration) {
    invertButtonArea(2);
    delay(max(50 - 20 * log10(duration), 0));
     if(duration > 1000){
      incrementMenuIndex();
    }
    if(duration > 5000){
      incrementMenuIndex();
      incrementMenuIndex();
      incrementMenuIndex();
    }
    incrementMenuIndex();
  });

}

void loop() {
  processMotor();
  renderDisplay();
  if(currentMenu == DEBUG_MENU){
    debugUpdate();
  }
  drawSelectedIndicator(menuIndex * 8);
  buttonsManager.checkButtons();

  absoluteTime = updateCurrentTime();

  // change time now too
  Serial.print(timeNow * 15 / 60); 
  Serial.print(":");
  Serial.println(timeNow * 15 - (timeNow * 15 / 60) * 60);


  if(!dispensed && timeNow >= dispenseTime){
    dispense();
    dispensed = true;
  }


  if(dispensed && timeNow < dispenseTime){
    dispensed = false;
  }
  
  endRenderDisplay();
}


