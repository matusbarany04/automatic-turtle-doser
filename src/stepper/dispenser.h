#ifndef DISPENSER_H
#define DISPENSER_H

#include <TinyStepper_28BYJ_48.h>

// Constants
extern const int MOTOR_IN1_PIN;
extern const int MOTOR_IN2_PIN;
extern const int MOTOR_IN3_PIN;
extern const int MOTOR_IN4_PIN;

// Global variables
extern bool isEmpty;
extern int slotCount;

// Global stepper motor instance
extern TinyStepper_28BYJ_48 stepper;

// Function declarations
void setupDispenser();
bool isDispenserEmpty();
void dispense();
void startConfiguration();
void stopConfiguration();
void stopRotation();

#endif // DISPENSER_H
