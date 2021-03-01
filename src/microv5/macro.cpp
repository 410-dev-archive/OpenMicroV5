#include "main.h"
#include "microv5/typeconvert.h"
#include "microv5/files.h"
#include "microv5/sensor.h"
#include "microv5/motor.h"
#include "microv5/macro.h"
#include "microv5/devices.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <numeric>

std::vector<int> loadedMacro_left{};
std::vector<int> loadedMacro_right{};
std::vector<int> loadedMacro_side{};

MDevices devices_mc;

void MMacro::recordMacro(std::string fileName) {
	MTypeConvert typeconvert;
	std::string encoderLeft = typeconvert.stringJoin(devices_mc.encLeft, ",");
	std::string encoderRight = typeconvert.stringJoin(devices_mc.encRight, ",");
	std::string encoderSide = typeconvert.stringJoin(devices_mc.encSide, ",");

  MFiles filemgr;

	filemgr.writeStringToFile(fileName + "_enc_Left", encoderLeft);
	filemgr.writeStringToFile(fileName + "_enc_Right", encoderRight);
	filemgr.writeStringToFile(fileName + "_enc_Side", encoderSide);
}


void MMacro::loadMacro(std::string loadedMacro_name) {
  MFiles filemgr;
	MTypeConvert typeconvert;
	MMotor motor;
	MSensor sensor;
	loadedMacro_left = typeconvert.stringSplitToInt(filemgr.readStringFromFile(loadedMacro_name + "_enc_Left"), " ");
	loadedMacro_right = typeconvert.stringSplitToInt(filemgr.readStringFromFile(loadedMacro_name + "_enc_Right"), " ");
	loadedMacro_side = typeconvert.stringSplitToInt(filemgr.readStringFromFile(loadedMacro_name + "_enc_Side"), " ");

	pros::Motor WHEEL_LEFT[] = {devices_mc.WHEEL_FRONT_LEFT(), devices_mc.WHEEL_BACK_LEFT()};
	pros::Motor WHEEL_RIGHT[] = {devices_mc.WHEEL_FRONT_RIGHT(), devices_mc.WHEEL_BACK_RIGHT()};
	pros::Motor MOTOR_PULLER[] = {devices_mc.MOTOR_PULLER_LEFT(), devices_mc.MOTOR_PULLER_RIGHT()};

	for (int i = 0; i < loadedMacro_left.size(); i++) {
		bool motorIsAlreadyRunning = false;
		short shouldStop = 0;
		while(shouldStop < 3) {
			shouldStop = 0;
			if (!motorIsAlreadyRunning) {
				if (loadedMacro_left.at(i) > 0) motor.motorRunMultiple(WHEEL_LEFT, 2, 100);
				if (loadedMacro_left.at(i) < 0) motor.motorRunReverseMultiple(WHEEL_LEFT, 2, 100);
				if (loadedMacro_right.at(i) > 0) motor.motorRunMultiple(WHEEL_RIGHT, 2, 100);
				if (loadedMacro_right.at(i) < 0) motor.motorRunReverseMultiple(WHEEL_RIGHT, 2, 100);
				if (loadedMacro_side.at(i) != 0) motor.motorRunMultiple(MOTOR_PULLER, 2, 100);
			}

			if (abs(loadedMacro_left.at(i) - sensor.getShaftEncoderData(devices_mc.ENCODER_LEFT())) < 2) {
				motor.motorStopMultiple(WHEEL_LEFT, 2);
				shouldStop++;
			}
			if (abs(loadedMacro_right.at(i) - sensor.getShaftEncoderData(devices_mc.ENCODER_RIGHT())) < 2) {
				motor.motorStopMultiple(WHEEL_RIGHT, 2);
				shouldStop++;
			}
			if (abs(loadedMacro_side.at(i) - sensor.getShaftEncoderData(devices_mc.ENCODER_SIDE())) < 2) {
				motor.motorStopMultiple(MOTOR_PULLER, 2);
				shouldStop++;
			}

		}
	}
}
