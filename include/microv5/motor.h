#include "main.h"

class MMotor {
public: void motorRunMultiple(pros::Motor specifiedMotors[], int motorCounts, int speed);
public: void motorRun(pros::Motor specifiedMotor, int speed);
public: void motorRunReverseMultiple(pros::Motor specifiedMotors[], int motorCounts, int speed);
public: void motorRunReverse(pros::Motor specifiedMotor, int speed);
public: void motorStop(pros::Motor specifiedMotor);
public: void motorStopMultiple(pros::Motor specifiedMotors[], int motorCounts);
};
