#include "main.h"
#include "microv5/devlist.h"
#include "microv5/motor.h"
#include "microv5/sensor.h"
#include "microv5/remote.h"
#include "microv5/typeconvert.h"

#include <vector>

bool actionUpdate = false;
bool liveControl = false;
float multiplier = 1.0;

std::string recentActivity = "";
std::string FWD = "";
std::string LFT = "";

float speed = 25.0;

MMotor motor;
MTypeConvert typeconvert;
MSensor sensor;

std::vector<int> MRemote::getRemoteButtonData() {
  int left = controller.get_analog(ANALOG_LEFT_Y);
  int right = controller.get_analog(ANALOG_RIGHT_Y);
  int digitalUp = controller.get_digital(DIGITAL_UP);
  int digitalDown = controller.get_digital(DIGITAL_DOWN);
  int 

  std::vector<int> returnData;
  returnData.push_back(left);
  returnData.push_back(right);
  returnData.push_back(digitalUp);
  returnData.push_back(digitalDown);
  return returnData;
}


void MRemote::updateAll() {

  if (!liveControl) {
    encLeft.at(encLeft.size() - 1) = sensor.getShaftEncoderData(ENCODER_LEFT);
    encRight.at(encRight.size() - 1) = sensor.getShaftEncoderData(ENCODER_RIGHT);
    encSide.at(encSide.size() - 1) = sensor.getShaftEncoderData(ENCODER_SIDE);
  }

  FWD = typeconvert.convertToString((int) controller.get_analog(ANALOG_LEFT_Y));
  LFT = typeconvert.convertToString((int) controller.get_analog(ANALOG_LEFT_X));

  std::vector<int> controlData = getRemoteButtonData();

  multiplier = 1.0;
  if (controller.get_digital(L1)) multiplier = 2.0;
  if (controller.get_digital(L2)) multiplier = 4.0;

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
  encLeft.push_back(0);
  encRight.push_back(0);
  encSide.push_back(0);

  MSensor sensor;

  sensor.resetShaftEncoderValue(ENCODER_LEFT);
  sensor.resetShaftEncoderValue(ENCODER_RIGHT);
  sensor.resetShaftEncoderValue(ENCODER_SIDE);
  actionUpdate = false;
}

void MRemote::onRelease_wheels() {
  if(actionUpdate && !liveControl) addIndex();
  recentActivity = "REMOTE: RELEASED";
  motor.motorStopMultiple(ALL_WHEELS, 4);
}

void MRemote::onPress_forward() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: FORWARD";
  motor.motorRunMultiple(ALL_WHEELS, 4, speed*multiplier);
}

void MRemote::onPress_backward() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: BACKWARD";
  motor.motorRunMultiple(ALL_WHEELS, 4, speed*multiplier);
}

void MRemote::onPress_turnLeft() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: LEFT";
  motor.motorRunMultiple(WHEEL_RIGHT, 2, speed*multiplier);
  motor.motorRunReverseMultiple(WHEEL_LEFT, 2, speed*multiplier);
}

void MRemote::onPress_turnRight() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: RIGHT";
  motor.motorRunMultiple(WHEEL_LEFT, 2, speed*multiplier);
  motor.motorRunReverseMultiple(WHEEL_RIGHT, 2, speed*multiplier);
}

void MRemote::onPress_startPuller() {
  if(!actionUpdate) actionUpdate = true;
  recentActivity = "REMOTE: PULL";
  motor.motorRunMultiple(MOTOR_PULLER, 2, speed*multiplier);
}

void MRemote::onRelease_puller() {
  motor.motorStopMultiple(MOTOR_PULLER, 2);
}
