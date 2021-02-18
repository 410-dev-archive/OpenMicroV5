#include "main.h"

void motorRunMultiple(pros::Motor specifiedMotors[], int motorCounts, int speed) {
  for(int i = 0; i < motorCounts; i++) {
    specifiedMotors[i] = speed;
  }
}

void motorRun(pros::Motor specifiedMotor, int speed) {
  specifiedMotor = speed;
}

void motorRunReverseMultiple(pros::Motor specifiedMotors[], int motorCounts, int speed) {
  for(int i = 0; i < motorCounts; i++) {
    specifiedMotors[i] = -speed;
  }
}

void motorRunReverse(pros::Motor specifiedMotor, int speed) {
  specifiedMotor = -speed;
}

void motorStop(pros::Motor specifiedMotor) {
  specifiedMotor = 0;
}

void motorStopMultiple(pros::Motor specifiedMotors[], int motorCounts) {
  for(int i = 0; i < motorCounts; i++) {
    specifiedMotors[i] = 0;
  }
}
