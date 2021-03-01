#include "main.h"

class MDisplay {
public: void print(std::string content);
public: void setLine(int specifiedLine, std::string content);
public: void clear();
public: void setPrintedLineTo(int lineNum);
public: int getPrintLine();
};
