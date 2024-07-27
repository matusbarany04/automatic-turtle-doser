#include "dispenser.h"

const int MOTOR_IN1_PIN = 18;
const int MOTOR_IN2_PIN = 19;
const int MOTOR_IN3_PIN = 20;
const int MOTOR_IN4_PIN = 22;
bool isEmpty = false;
int slotCount = 12; // Assuming a default slot count, adjust as necessary

// Global stepper motor instance
HalfStepMotor stepper = HalfStepMotor::fromPins(MOTOR_IN1_PIN, MOTOR_IN2_PIN, MOTOR_IN3_PIN, MOTOR_IN4_PIN);

void setupDispenser() {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    // Initialize the stepper motor here
    // stepper.setSpeedInStepsPerSecond(500);
    // stepper.setAccelerationInStepsPerSecondPerSecond(512);
}

bool isDispenserEmpty() {
    return isEmpty;
}

void dispense() {
    stepper.stepDegrees(360 / slotCount);
}

void startConfiguration() {
    // Implement configuration start logic here
}

void stopConfiguration() {
    // Implement configuration stop logic here
}

void stopRotation() {
    // Implement rotation stop logic here
}
