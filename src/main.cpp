#include "main.h"
#include "microv5/devices.h"
#include "microv5/typeconvert.h"
#include "microv5/display.h"
#include "microv5/remote.h"
#include <vector>

std::string SYSVERSION = "1.0a1b201228";

void on_center_button() {}

void initialize() {
	MDisplay display;
	display.print("OpenMicroV5 - VexV5 Micro Operating System");
	display.print("Powered by AVER Software");
	display.print("System Version " + SYSVERSION);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	MDisplay display;
	display.print("Start Mode: Competition");
	display.print("System is not ready.");
	display.print("Redirecting to OP control...");
	opcontrol();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	MDisplay display;
	display.print("Start Mode: Autonomous");
	display.print("System is not ready.");
	display.print("Redirecting to OP control...");
	opcontrol();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	MDisplay display;
	display.print("Start Mode: Operator Control");
	MRemote remote;
	MTypeConvert typeconvert;
	while (true) {
		std::vector<int> controllerStatusData = remote.getRemoteButtonData();
		remote.updateAll();
		display.setLine(display.getPrintLine() + 1, "Left Y Axis: " + typeconvert.convertToString(controllerStatusData.at(0)));
		display.setLine(display.getPrintLine() + 2, "Right Y Axis: " + typeconvert.convertToString(controllerStatusData.at(1)));
		display.setLine(display.getPrintLine() + 3, "Button Up: " + typeconvert.convertToString(controllerStatusData.at(2)));
		display.setLine(display.getPrintLine() + 4, "Button Down: " + typeconvert.convertToString(controllerStatusData.at(3)));
		pros::delay(20);
	}
}
