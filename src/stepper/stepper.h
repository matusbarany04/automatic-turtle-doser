#ifndef HALFSTEPMOTOR_H
#define HALFSTEPMOTOR_H

#include <Arduino.h>

class HalfStepMotor {
private:
    static const int maxpos = 4096;
    static const int stepms = 3;
    static const int states[8][4];

    int pins[4];
    int _state;
    int _pos;

    void _step(int dir);

public:
    HalfStepMotor(int p1, int p2, int p3, int p4);

    int pos() const;
    void reset();
    void step(int steps);
    void stepUntil(int target, int dir = 0);
    void stepUntilAngle(float angle, int dir = 0);
    void stepDegrees(float degrees);

    static HalfStepMotor fromPins(int p1, int p2, int p3, int p4);

};

#endif // HALFSTEPMOTOR_H
