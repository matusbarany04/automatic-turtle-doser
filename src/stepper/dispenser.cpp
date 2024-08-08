#include "dispenser.h"
#include <TinyStepper_28BYJ_48.h>

const int MOTOR_IN1_PIN = 22;
const int MOTOR_IN2_PIN = 20;
const int MOTOR_IN3_PIN = 19;
const int MOTOR_IN4_PIN = 18;
bool stopFlag = false;
bool isEmpty = false;
int slotCount = 12; // Assuming a default slot count, adjust as necessary

// Global stepper motor instance
// HalfStepMotor stepper = HalfStepMotor::fromPins(MOTOR_IN1_PIN, MOTOR_IN2_PIN, MOTOR_IN3_PIN, MOTOR_IN4_PIN);

TinyStepper_28BYJ_48 stepper;

void setupDispenser() {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    // Initialize the stepper motor here
    stepper.setSpeedInStepsPerSecond(500);
    stepper.setAccelerationInStepsPerSecondPerSecond(512);

    stepper.connectToPins(MOTOR_IN1_PIN, MOTOR_IN2_PIN, MOTOR_IN3_PIN, MOTOR_IN4_PIN);
}

bool isDispenserEmpty() {
    return isEmpty;
}

void dispense() {
    stepper.setSpeedInStepsPerSecond(500);
    stepper.setAccelerationInStepsPerSecondPerSecond(512);
    stepper.moveRelativeInSteps(2048 / slotCount);
}

void startConfiguration() {
    stepper.setSpeedInStepsPerSecond(200);
    stepper.setAccelerationInStepsPerSecondPerSecond(512);
    stepper.setupMoveInSteps(2048 * 1000);
    // Implement configuration start logic here
    // move stepper motor slowly without blocking the thread
    stopFlag = false;
}

void stopConfiguration() {
    // Implement configuration stop logic here
    //stop motor movement
    stopFlag = true;
    stepper.setupStop();
}

void processMotor() {

    if(!stopFlag && !stepper.motionComplete()){
        stepper.processMovement();
    }
}
