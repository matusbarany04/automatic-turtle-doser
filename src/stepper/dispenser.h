#ifndef DISPENSER_H
#define DISPENSER_H

#include "stepper.h"

// Constants
extern const int MOTOR_IN1_PIN;
extern const int MOTOR_IN2_PIN;
extern const int MOTOR_IN3_PIN;
extern const int MOTOR_IN4_PIN;

// Global variables
extern bool isEmpty;
extern int slotCount;

// Global stepper motor instance
extern HalfStepMotor stepper;

// Function declarations
void setupDispenser();
bool isDispenserEmpty();
void dispense();
void startConfiguration();
void stopConfiguration();
void stopRotation();

#endif // DISPENSER_H
