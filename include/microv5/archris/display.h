#include "main.h"
#include <string.h>

void dispSetLine(int specifiedLine, std::string content) {
  pros::lcd::clear_line(specifiedLine);
  pros::lcd::set_text(specifiedLine, content);
}
