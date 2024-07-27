
#include "dispenser.h"


const int MOTOR_IN1_PIN = 18;
const int MOTOR_IN2_PIN = 19;
const int MOTOR_IN3_PIN = 20;
const int MOTOR_IN4_PIN = 21;

// Constructor implementation

Dispenser::Dispenser() {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    stepper = HalfStepMotor::fromPins(MOTOR_IN1_PIN, MOTOR_IN2_PIN, MOTOR_IN3_PIN, MOTOR_IN4_PIN);

    // Initialize the stepper motor here
    // stepper = getStepperMotor(); // Adjust as necessary
    // Ensure you have the correct initialization
    // stepper.setSpeedInStepsPerSecond(500);
    // stepper.setAccelerationInStepsPerSecondPerSecond(512);
}


// Method implementations
bool Dispenser::isDispenserEmpty() const {
    return isEmpty;
}

void Dispenser::dispense() {
    // stepper.moveRelativeInSteps(2048 / slotCount);
}

void Dispenser::startConfiguration() {
    // Implement configuration start logic here
}

void Dispenser::stopConfiguration() {
    // Implement configuration stop logic here
}

void Dispenser::stopRotation() {
    // Implement rotation stop logic here
}
