#include "main.h"

#include "microv5/devlist.h"
#include "microv5/hardlinker.h"

#include "microv5/typeconvert.h"
#include "microv5/display.h"
#include "microv5/remotecontrol.h"

#include <vector>

std::string SYSVERSION = "1.0a1b201228";
void on_center_button() {}

void initialize() {
	// dispPrint("OpenMicroV5 - VexV5 Micro Operating System");
	// dispPrint("Powered by AVER Software");
	// dispPrint("System Version " + SYSVERSION);
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
	// dispPrint("Start Mode: Competition");
	// dispPrint("System is not ready.");
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
	// dispPrint("Start Mode: Autonomous");
	// dispPrint("System is not ready.");
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
	//dispPrint("Start Mode: Operator Control");

	while (true) {
		// std::vector<int> controllerStatusData = getRemoteData();
		// dispSetLine(lastPrintedLine + 1, "Left Y Axis: " + convertToString(controllerStatusData.at(0)));
		// dispSetLine(lastPrintedLine + 2, "Right Y Axis: " + convertToString(controllerStatusData.at(1)));
		// dispSetLine(lastPrintedLine + 3, "Button Up: " + convertToString(controllerStatusData.at(2)));
		// dispSetLine(lastPrintedLine + 4, "Button Down: " + convertToString(controllerStatusData.at(3)));

		pros::delay(20);
	}
}
