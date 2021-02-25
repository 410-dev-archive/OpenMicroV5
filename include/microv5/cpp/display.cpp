#include "main.h"
#include <string.h>
#include "microv5/display.h"

int lastPrintedLine = 0;

void MDisplay::print(std::string content) {
  lastPrintedLine += 1;
  pros::lcd::set_text(lastPrintedLine, content);
}

void MDisplay::setLine(int specifiedLine, std::string content) {
  pros::lcd::clear_line(specifiedLine);
  pros::lcd::set_text(specifiedLine, content);
}

void MDisplay::clear() {
  pros::lcd::clear();
  lastPrintedLine = 0;
}

void MDisplay::setPrintedLineTo(int lineNum) {
  lastPrintedLine = lineNum;
}
