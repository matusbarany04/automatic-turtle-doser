#include <Arduino.h>
// #include <display/display.h>
#include <stepper/stepper.h>
#include <stepper/dispenser.h>
#include <cstdlib>
// Create a Dispenser object

#include <TinyStepper_28BYJ_48.h>

Dispenser dispenser;
const int buttonPin = 27;

// The setup routine runs once when you press reset:
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);               // Initialize serial communication
  Serial.println("Setup complete. Press the button to simulate a crash.");

  // Initialize the digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  
  
  // Initialize the dispenser
  // No need to use `new` for stack-allocated objects
}

// The loop routine runs over and over again forever:
void loop() {
  // blink(); // Assuming you have a function to blink an LED
    // TinyStepper_28BYJ_48 stepper = getStepperMotor();

    // stepper.moveRelativeInSteps(2048);
  // Dispense

    //
  // Note: This example uses "relative" motions.  This means that each
  // command will move the number of steps given, starting from it's 
  // current position.
  //

  //
  // set the speed and acceleration rates for the stepper motor
  //
  // stepper.setSpeedInStepsPerSecond(256);
  // stepper.setAccelerationInStepsPerSecondPerSecond(512);

  //
  // Rotate the motor in the forward direction one revolution (2048 steps). 
  // This function call will not return until the motion is complete.
  //
  // stepper.moveRelativeInSteps(2048);
  
  //
  // now that the rotation has finished, delay 1 second before starting 
  // the next move
  //
  delay(1000);

  dispenser.dispense();
  // delay(1000); 

  if (digitalRead(buttonPin) == HIGH) { 
    // Check if button is pressed
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
    digitalWrite(LED_BUILTIN, HIGH);
    exit(0);
  }

}

