#include "main.h"

class MSensor {
public: int getShaftEncoderData(pros::ADIEncoder encoder);
public: void resetShaftEncoderValue(pros::ADIEncoder encoder);
public: int snGetMotorEncoderData(pros::ADIEncoder encoder);
public: void snGetVisionSensorData(pros::ADIEncoder encoder);
public: void snSetShaftEncoderData(pros::ADIEncoder encoder);
public: void snSetMotorEncoderData(pros::ADIEncoder encoder);
};
