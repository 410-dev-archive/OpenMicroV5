#include "main.h"
#include "microv5/motor.h"

void MMotor::motorRunMultiple(pros::Motor specifiedMotors[], int motorCounts, int speed) {
  for(int i = 0; i < motorCounts; i++) {
    specifiedMotors[i].move(speed);
  }
}

void MMotor::motorRun(pros::Motor specifiedMotor, int speed) {
  specifiedMotor.move(speed);
}

void MMotor::motorRunReverseMultiple(pros::Motor specifiedMotors[], int motorCounts, int speed) {
  for(int i = 0; i < motorCounts; i++) {
    specifiedMotors[i].move(-speed);
  }
}

void MMotor::motorRunReverse(pros::Motor specifiedMotor, int speed) {
  specifiedMotor.move(-speed);
}

void MMotor::motorStop(pros::Motor specifiedMotor) {
  specifiedMotor.move(0);
}

void MMotor::motorStopMultiple(pros::Motor specifiedMotors[], int motorCounts) {
  for(int i = 0; i < motorCounts; i++) {
    specifiedMotors[i].move(0);
  }
}
