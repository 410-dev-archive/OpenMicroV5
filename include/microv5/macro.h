// This code is dependent on ARCHCIS

#include "main.h"
#include "microv5/archcis/typeconvert.h"
#include "microv5/archcis/files.h"
#include "microv5/archcis/sensor.h"
#include "microv5/archcis/motor.h"
#include "microv5/devlist.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <numeric>

std::vector<int> loadedMacro_left{};
std::vector<int> loadedMacro_right{};
std::vector<int> loadedMacro_side{};

void recordMacro(std::string fileName) {
	std::string encoderLeft = stringJoin(encLeft, ",");
	std::string encoderRight = stringJoin(encRight, ",");
	std::string encoderSide = stringJoin(encSide, ",");

	fWriteStringToFile(fileName + "_enc_Left", encoderLeft);
	fWriteStringToFile(fileName + "_enc_Right", encoderRight);
	fWriteStringToFile(fileName + "_enc_Side", encoderSide);
}


void loadMacro(std::string loadedMacro_name) {
	loadedMacro_left = stringSplitToInt(fReadStringFromFile(loadedMacro_name + "_enc_Left"), " ");
	loadedMacro_right = stringSplitToInt(fReadStringFromFile(loadedMacro_name + "_enc_Right"), " ");
	loadedMacro_side = stringSplitToInt(fReadStringFromFile(loadedMacro_name + "_enc_Side"), " ");

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
