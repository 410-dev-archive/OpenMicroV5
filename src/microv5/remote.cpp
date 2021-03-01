#include "main.h"
#include "microv5/motor.h"
#include "microv5/sensor.h"
#include "microv5/remote.h"
#include "microv5/typeconvert.h"
#include "microv5/devices.h"
#include <vector>

bool actionUpdate = false;
bool liveControl = false;
float multiplier = 1.0;

std::string recentActivity = "";

float speed = 25.0;

MDevices devices;

std::vector<int> MRemote::getRemoteButtonData() {
  pros::Controller controller(pros::E_CONTROLLER_MASTER);
  int left = controller.get_analog(ANALOG_LEFT_Y);
  int right = controller.get_analog(ANALOG_RIGHT_Y);
  int digitalUp = controller.get_digital(DIGITAL_UP);
  int digitalDown = controller.get_digital(DIGITAL_DOWN);
  int l1 = controller.get_digital(DIGITAL_L1);
  int l2 = controller.get_digital(DIGITAL_L2);

  std::vector<int> returnData;
  returnData.push_back(left);
  returnData.push_back(right);
  returnData.push_back(digitalUp);
  returnData.push_back(digitalDown);
  returnData.push_back(l1);
  returnData.push_back(l2);
  return returnData;
}


void MRemote::updateAll() {
  MSensor sensor;
  if (!liveControl) {
    devices.encLeft.at(devices.encLeft.size() - 1) = sensor.getShaftEncoderData(devices.ENCODER_LEFT());
    devices.encRight.at(devices.encRight.size() - 1) = sensor.getShaftEncoderData(devices.ENCODER_RIGHT());
    devices.encSide.at(devices.encSide.size() - 1) = sensor.getShaftEncoderData(devices.ENCODER_SIDE());
  }

  std::vector<int> controlData = getRemoteButtonData();

  multiplier = 1.0;
  if (controlData.at(4)) multiplier = 2.0;
  if (controlData.at(5)) multiplier = 4.0;

  if (controlData.at(0) > 120) onPress_forward();
  else if (controlData.at(0) < -120) onPress_backward();
  else if (controlData.at(1) > 120) onPress_turnLeft();
  else if (controlData.at(1) < -120) onPress_turnRight();
  else if (controlData.at(2) == 1) onPress_startPuller();
  else{
    onRelease_wheels();
    onRelease_puller();
  }
}

void MRemote::addIndex() {
  devices.encLeft.push_back(0);
  devices.encRight.push_back(0);
  devices.encSide.push_back(0);

  MSensor sensor;
  sensor.resetShaftEncoderValue(devices.ENCODER_LEFT());
  sensor.resetShaftEncoderValue(devices.ENCODER_RIGHT());
  sensor.resetShaftEncoderValue(devices.ENCODER_SIDE());
  actionUpdate = false;
}

void MRemote::onRelease_wheels() {
  if(actionUpdate && !liveControl) addIndex();
  recentActivity = "REMOTE: RELEASED";
  MMotor motor;
  motor.motorStop(devices.WHEEL_BACK_LEFT());
  motor.motorStop(devices.WHEEL_BACK_RIGHT());
  motor.motorStop(devices.WHEEL_FRONT_LEFT());
  motor.motorStop(devices.WHEEL_FRONT_RIGHT());
}

void MRemote::onPress_forward() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: FORWARD";
  MMotor motor;
  motor.motorRun(devices.WHEEL_BACK_LEFT(), speed*multiplier);
  motor.motorRun(devices.WHEEL_BACK_RIGHT(), speed*multiplier);
  motor.motorRun(devices.WHEEL_FRONT_LEFT(), speed*multiplier);
  motor.motorRun(devices.WHEEL_FRONT_RIGHT(), speed*multiplier);
}

void MRemote::onPress_backward() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: BACKWARD";
  MMotor motor;
  motor.motorRunReverse(devices.WHEEL_BACK_LEFT(), speed*multiplier);
  motor.motorRunReverse(devices.WHEEL_BACK_RIGHT(), speed*multiplier);
  motor.motorRunReverse(devices.WHEEL_FRONT_LEFT(), speed*multiplier);
  motor.motorRunReverse(devices.WHEEL_FRONT_RIGHT(), speed*multiplier);
}

void MRemote::onPress_turnLeft() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: LEFT";
  MMotor motor;
  motor.motorRun(devices.WHEEL_BACK_RIGHT(), speed*multiplier);
  motor.motorRun(devices.WHEEL_FRONT_RIGHT(), speed*multiplier);
  motor.motorRunReverse(devices.WHEEL_BACK_LEFT(), speed*multiplier);
  motor.motorRunReverse(devices.WHEEL_FRONT_LEFT(), speed*multiplier);
}

void MRemote::onPress_turnRight() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: RIGHT";
  MMotor motor;
  motor.motorRunReverse(devices.WHEEL_BACK_RIGHT(), speed*multiplier);
  motor.motorRunReverse(devices.WHEEL_FRONT_RIGHT(), speed*multiplier);
  motor.motorRun(devices.WHEEL_BACK_LEFT(), speed*multiplier);
  motor.motorRun(devices.WHEEL_FRONT_LEFT(), speed*multiplier);
}

void MRemote::onPress_startPuller() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: PULL";
  MMotor motor;
  motor.motorRun(devices.MOTOR_PULLER_LEFT(), speed*multiplier);
  motor.motorRun(devices.MOTOR_PULLER_RIGHT(), speed*multiplier);
  motor.motorRun(devices.MOTOR_FRONTARM_LEFT(), speed*multiplier);
  motor.motorRun(devices.MOTOR_FRONTARM_RIGHT(), speed*multiplier);
}

void MRemote::onRelease_puller() {
  MMotor motor;
  motor.motorStop(devices.MOTOR_PULLER_LEFT());
  motor.motorStop(devices.MOTOR_PULLER_RIGHT());
  motor.motorStop(devices.MOTOR_FRONTARM_LEFT());
  motor.motorStop(devices.MOTOR_FRONTARM_RIGHT());
}
