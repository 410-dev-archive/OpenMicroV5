#include "main.h"
#include "microv5/typeconvert.h"
#include "microv5/files.h"
#include "microv5/sensor.h"
#include "microv5/motor.h"
#include "microv5/devlist.h"
#include "microv5/macro.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <numeric>

std::vector<int> loadedMacro_left{};
std::vector<int> loadedMacro_right{};
std::vector<int> loadedMacro_side{};

void MMacro::recordMacro(std::string fileName) {
	std::string encoderLeft = stringJoin(encLeft, ",");
	std::string encoderRight = stringJoin(encRight, ",");
	std::string encoderSide = stringJoin(encSide, ",");

  MFiles filemgr;

	filemgr.writeStringToFile(fileName + "_enc_Left", encoderLeft);
	filemgr.writeStringToFile(fileName + "_enc_Right", encoderRight);
	filemgr.writeStringToFile(fileName + "_enc_Side", encoderSide);
}


void MMacro::loadMacro(std::string loadedMacro_name) {
  MFiles filemgr;
	loadedMacro_left = stringSplitToInt(filemgr.readStringFromFile(loadedMacro_name + "_enc_Left"), " ");
	loadedMacro_right = stringSplitToInt(filemgr.readStringFromFile(loadedMacro_name + "_enc_Right"), " ");
	loadedMacro_side = stringSplitToInt(filemgr.readStringFromFile(loadedMacro_name + "_enc_Side"), " ");

	for (int i = 0; i < loadedMacro_left.size(); i++) {
		bool motorIsAlreadyRunning = false;
		short shouldStop = 0;
		while(shouldStop < 3) {
			shouldStop = 0;
			if (!motorIsAlreadyRunning) {
				if (loadedMacro_left.at(i) > 0) motorRunMultiple(WHEEL_LEFT, 2, 100);
				if (loadedMacro_left.at(i) < 0) motorRunReverseMultiple(WHEEL_LEFT, 2, 100);
				if (loadedMacro_right.at(i) > 0) motorRunMultiple(WHEEL_RIGHT, 2, 100);
				if (loadedMacro_right.at(i) < 0) motorRunReverseMultiple(WHEEL_RIGHT, 2, 100);
				if (loadedMacro_side.at(i) != 0) motorRunMultiple(MOTOR_PULLER, 2, 100);
			}

			if (abs(loadedMacro_left.at(i) - snGetShaftEncoderData(ENCODER_LEFT)) < 2) {
				motorStopMultiple(WHEEL_LEFT, 2);
				shouldStop++;
			}
			if (abs(loadedMacro_right.at(i) - snGetShaftEncoderData(ENCODER_RIGHT)) < 2) {
				motorStopMultiple(WHEEL_RIGHT, 2);
				shouldStop++;
			}
			if (abs(loadedMacro_side.at(i) - snGetShaftEncoderData(ENCODER_SIDE)) < 2) {
				motorStopMultiple(MOTOR_PULLER, 2);
				shouldStop++;
			}

		}
	}
}
