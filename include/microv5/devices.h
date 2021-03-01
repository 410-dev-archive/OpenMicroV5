#include "main.h"

class MDevices {
public: std::vector<int> encLeft = {0, 0};
public: std::vector<int> encRight = {0, 0};
public: std::vector<int> encSide = {0, 0};
public: static pros::Motor MOTOR_PULLER_LEFT();
public: static pros::Motor MOTOR_PULLER_RIGHT();
public: static pros::Motor WHEEL_FRONT_LEFT();
public: static pros::Motor WHEEL_FRONT_RIGHT();
public: static pros::Motor WHEEL_BACK_LEFT();
public: static pros::Motor WHEEL_BACK_RIGHT();
public: static pros::Motor MOTOR_FRONTARM_LEFT();
public: static pros::Motor MOTOR_FRONTARM_RIGHT();
public: static pros::ADIEncoder ENCODER_LEFT();
public: static pros::ADIEncoder ENCODER_RIGHT();
public: static pros::ADIEncoder ENCODER_SIDE();
};
