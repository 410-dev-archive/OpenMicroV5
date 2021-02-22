#include "main.h"

int getShaftEncoderData(pros::ADIEncoder encoder) {
	return encoder.get_value();
}

void resetShaftEncoderValue(pros::ADIEncoder encoder) {
	encoder.reset();
}

int snGetMotorEncoderData(pros::ADIEncoder encoder) {

}

void snGetVisionSensorData(pros::ADIEncoder encoder) {

}

void snSetShaftEncoderData(pros::ADIEncoder encoder) {

}

void snSetMotorEncoderData(pros::ADIEncoder encoder) {

}
