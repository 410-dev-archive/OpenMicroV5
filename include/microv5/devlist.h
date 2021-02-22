#include "main.h"
#include <vector>

// You may edit this

pros::Motor WHEEL_FRONT_LEFT(3);
pros::Motor WHEEL_FRONT_RIGHT(5);
pros::Motor WHEEL_BACK_LEFT(4);
pros::Motor WHEEL_BACK_RIGHT(6);

pros::Motor MOTOR_FRONTARM_LEFT(8);
pros::Motor MOTOR_FRONTARM_RIGHT(7);

pros::Motor MOTOR_PULLER_LEFT(1);
pros::Motor MOTOR_PULLER_RIGHT(2);

pros::ADIEncoder ENCODER_LEFT();
pros::ADIEncoder ENCODER_RIGHT();
pros::ADIEncoder ENCODER_SIDE();

pros::Motor WHEEL_LEFT[] = {WHEEL_FRONT_LEFT, WHEEL_BACK_LEFT};
pros::Motor WHEEL_RIGHT[] = {WHEEL_FRONT_RIGHT, WHEEL_BACK_RIGHT};
pros::Motor MOTOR_PULLER[] = {MOTOR_PULLER_LEFT, MOTOR_PULLER_RIGHT};

std::vector<int> encLeft = {0, 0};
std::vector<int> encRight = {0, 0};
std::vector<int> encSide = {0, 0};
