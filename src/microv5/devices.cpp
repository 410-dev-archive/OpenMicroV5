#include "main.h"
#include "microv5/devices.h"

pros::Motor MDevices::MOTOR_PULLER_LEFT() {return pros::Motor(1);}
pros::Motor MDevices::MOTOR_PULLER_RIGHT() {return pros::Motor(2);}

pros::Motor MDevices::WHEEL_FRONT_LEFT() {return pros::Motor(3);}
pros::Motor MDevices::WHEEL_FRONT_RIGHT() {return pros::Motor(5);}
pros::Motor MDevices::WHEEL_BACK_LEFT() {return pros::Motor(4);}
pros::Motor MDevices::WHEEL_BACK_RIGHT() {return pros::Motor(6);}

pros::Motor MDevices::MOTOR_FRONTARM_LEFT() {return pros::Motor(8);}
pros::Motor MDevices::MOTOR_FRONTARM_RIGHT() {return pros::Motor(7);}

pros::ADIEncoder MDevices::ENCODER_LEFT() {return pros::ADIEncoder(1,2);}
pros::ADIEncoder MDevices::ENCODER_RIGHT() {return pros::ADIEncoder(3,4);}
pros::ADIEncoder MDevices::ENCODER_SIDE() {return pros::ADIEncoder(5,6);}
