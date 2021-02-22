#include "main.h"
#include "microv5/archris/devlist.h"
#include "microv5/archcis/motor.h"
#include "microv5/archris/sensor.h"

bool actionUpdate = false;
bool liveControl = false;
float multiplier = 1.0;

string recentActivity = "";
string FWD = "";
string LFT = "";

float speed = 25.0;

void updateAll(pros::Controller ctrl) {

  if (!liveControl) {
    encLeft.at(encLeft.size() - 1) = getShaftEncoderData(ENCODER_LEFT);
    encRight.at(encRight.size() - 1) = getShaftEncoderData(ENCODER_RIGHT);
    encSide.at(encSide.size() - 1) = getShaftEncoderData(ENCODER_SIDE);
  }

  FWD = toString(ctrl.get_analog(ANALOG_LEFT_Y));
  LFT = toString(ctrl.get_analog(ANALOG_LEFT_X));

  multiplier = 1.0;
  if (ctrl.get_digital(L1)) multiplier = 2.0;
  if (ctrl.get_digital(L2)) multiplier = 4.0;

  if (ctrl.get_digital(UP) || ctrl.get_analog(ANALOG_LEFT_Y) > 120) onPress_forward();
  else if (ctrl.get_digital(DOWN) || ctrl.get_analog(ANALOG_LEFT_Y) < -120) onPress_backward();
  else if (ctrl.get_digital(LEFT) || ctrl.get_analog(ANALOG_LEFT_X) < -120 || Controller.Axis1.value() < -120) onPress_turnRight();
  else if (ctrl.get_digital(RIGHT) || ctrl.get_analog(ANALOG_LEFT_X) > 120 || Controller.Axis1.value() > 120) onPress_turnLeft();
  else if (ctrl.get_digital(X) || ctrl.get_analog(ANALOG_RIGHT_Y) > 120) onPress_startPuller();
  else{
    onRelease_wheels();
    onRelease_puller();
  }
  if (Controller.ButtonA.pressing()) onPress_systemTerminate();
}

void addIndex() {
  encLeft.push_back(0);
  encRight.push_back(0);
  encSide.push_back(0);
  resetShaftEncoderValue(ENCODER_LEFT);
  resetShaftEncoderValue(ENCODER_RIGHT);
  resetShaftEncoderValue(ENCODER_SIDE);
  actionUpdate = false;
}

void onRelease_wheels() {
  if(actionUpdate && !liveControl) addIndex();
  recentActivity = "REMOTE: RELEASED";
  motor allmotors[] = {WHEEL_FRONT_LEFT,WHEEL_BACK_RIGHT,WHEEL_BACK_LEFT,WHEEL_FRONT_RIGHT};
  mtctl.stopMotors(allmotors, 4);
}

void onPress_forward() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: FORWARD";
  motor allmotors[] = {WHEEL_FRONT_LEFT,WHEEL_BACK_RIGHT,WHEEL_BACK_LEFT,WHEEL_FRONT_RIGHT};
  mtctl.runMotors(allmotors, 4, directionType::rev, speed*multiplier);
}

void onPress_backward() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: BACKWARD";
  motor allmotors[] = {WHEEL_FRONT_LEFT,WHEEL_BACK_RIGHT,WHEEL_BACK_LEFT,WHEEL_FRONT_RIGHT};
  mtctl.runMotors(allmotors, 4, directionType::fwd, speed*multiplier);
}

void onPress_turnLeft() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: LEFT";
  motor toRunForward[] = {WHEEL_FRONT_RIGHT, WHEEL_BACK_RIGHT};
  motor toRunBackward[] = {WHEEL_FRONT_LEFT, WHEEL_BACK_LEFT};
  mtctl.runMotors(toRunForward, 2, directionType::fwd, speed*multiplier);
  mtctl.runMotors(toRunBackward, 2, directionType::rev, speed*multiplier);
}

void onPress_turnRight() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: RIGHT";
  motor toRunBackward[] = {WHEEL_FRONT_RIGHT, WHEEL_BACK_RIGHT};
  motor toRunForward[] = {WHEEL_FRONT_LEFT, WHEEL_BACK_LEFT};
  mtctl.runMotors(toRunForward, 2, directionType::fwd, speed*multiplier);
  mtctl.runMotors(toRunBackward, 2, directionType::rev, speed*multiplier);
}

void onPress_startPuller() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: PULL";
  motor pullers[] = {PULL_MOTOR_1, PULL_MOTOR_2, INTAKE_LEFT, INTAKE_RIGHT};
  mtctl.runMotors(pullers, 4, directionType::fwd, speed*multiplier);
}

void onRelease_puller() {
  motor pullers[] = {PULL_MOTOR_1, PULL_MOTOR_2, INTAKE_LEFT, INTAKE_RIGHT};
  mtctl.stopMotors(pullers, 4);
}

void onPress_systemTerminate() {
  recentActivity = "REMOTE: STOP";
  mtctl.stopMotors(MOTOR_ALL, 8);
}
