#include "main.h"

void motorRun(pros::Motor specifiedMotor, int speed) {
  specifiedMotor.move(speed);
}
