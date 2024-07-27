#ifndef DISPENSER_H
#define DISPENSER_H

#include "stepper.h"
// #include <TinyStepper_28BYJ_48.h>

class Dispenser {
private:
    bool isEmpty;                    // true if dispenser is empty
    static const int slotCount = 12; // Total number of slots
    HalfStepMotor stepper;    // Stepper motor object

public:
    // Constructor
    Dispenser();

    // Methods
    bool isDispenserEmpty() const;
    void dispense();
    void startConfiguration();
    void stopConfiguration();
    void stopRotation();
};

#endif // DISPENSER_H
