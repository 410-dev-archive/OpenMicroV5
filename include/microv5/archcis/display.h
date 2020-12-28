#include "main.h"
#include <string.h>
int lastPrintedLine = 0;

void dispPrint(std::string content) {
  lastPrintedLine += 1;
  pros::lcd::set_text(lastPrintedLine, content);
}

void dispSetLine(int specifiedLine, std::string content) {
  pros::lcd::clear_line(specifiedLine);
  pros::lcd::set_text(specifiedLine, content);
}

void dispClear() {
  pros::lcd::clear();
  lastPrintedLine = 0;
}

void dispSetPrintedLineTo(int lineNum) {
  lastPrintedLine = lineNum;
}
