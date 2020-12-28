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
