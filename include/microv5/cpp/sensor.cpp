#include "main.h"
#include "microv5/sensor.h"

int MSensor::getShaftEncoderData(pros::ADIEncoder encoder) {
	return encoder.get_value();
}

void MSensor::resetShaftEncoderValue(pros::ADIEncoder encoder) {
	encoder.reset();
}

int MSensor::snGetMotorEncoderData(pros::ADIEncoder encoder) {

}

void MSensor::snGetVisionSensorData(pros::ADIEncoder encoder) {

}

void MSensor::snSetShaftEncoderData(pros::ADIEncoder encoder) {

}

void MSensor::snSetMotorEncoderData(pros::ADIEncoder encoder) {

}
