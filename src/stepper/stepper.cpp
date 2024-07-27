#include <Arduino.h>


class HalfStepMotor {
private:
    static const int maxpos = 4096;
    static const int stepms = 3;
    static const int states[8][4];

    int pins[4];
    int _state;
    int _pos;

    void _step(int dir) {
        const int* state = states[_state];

        for (int i = 0; i < 4; ++i) {
            digitalWrite(pins[i], state[i]);
        }

        _state = (_state + dir + 8) % 8; // Ensure state wraps around
        _pos = (_pos + dir + maxpos) % maxpos; // Ensure position wraps around
    }

public:
    HalfStepMotor(int p1, int p2, int p3, int p4)
        : _state(0), _pos(0) {
        pins[0] = p1;
        pins[1] = p2;
        pins[2] = p3;
        pins[3] = p4;

        for (int i = 0; i < 4; ++i) {
            pinMode(pins[i], OUTPUT);
        }
    }

    ~HalfStepMotor() = default;

    int pos() const { return _pos; }

    void reset() { _pos = 0; }

    void step(int steps) {
        int dir = (steps >= 0) ? 1 : -1;
        steps = abs(steps);

        for (int i = 0; i < steps; ++i) {
            unsigned long t_start = millis();

            _step(dir);

            unsigned long t_end = millis();
            unsigned long t_delta = t_end - t_start;
            delay(stepms - t_delta);
        }
    }
    static HalfStepMotor fromPins(int p1, int p2, int p3, int p4) {
      return HalfStepMotor(p1, p2, p3, p4);
    }

    void stepUntil(int target, int dir = 0) {
        if (target < 0 || target > maxpos) {
            Serial.print("Value out of range: ");
            Serial.println(target);
            return;
        }

        if (dir == 0) {
            dir = (target > _pos) ? 1 : -1;
            if (abs(target - _pos) > maxpos / 2) {
                dir = -dir;
            }
        }

        while (_pos != target) {
            step(dir);
        }
    }

    void stepUntilAngle(float angle, int dir = 0) {
        if (angle < 0 || angle > 360) {
            Serial.print("Angle out of range: ");
            Serial.println(angle);
            return;
        }

        int target = static_cast<int>(angle / 360 * maxpos);
        stepUntil(target, dir);
    }

    void stepDegrees(float degrees) {
        if (degrees < 0 || degrees > 360) {
            Serial.println("Degrees should be between 0 and 360");
            return;
        }

        int stepsToTake = static_cast<int>(degrees / 360 * maxpos);
        reset();
        step(stepsToTake);
    }
};

const int HalfStepMotor::states[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};
