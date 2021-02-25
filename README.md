# Project OpenMicroV5 System

----

### PROS API based VexV5 Controller Kernel

OpenMicroV5 is basically an instruction set, that will make the development for VexV5 easier and faster.

Developer may choose architecture: 

1. CIS (Complex Instruction Set)
2. RIS (Reduced Instuction Sets)



IT IS STRONGLY NOT RECOMMENDED TO USE BOTH CIS AND RIS, BECAUSE THERE MAY BE DUPLICATED FUNCTIONS.

To use CIS, change the header inclusion code to following:

`#include "microv5/header.h"`

To use RIS, change the header inclusion code to following:

`#include "microv5/archris/header.h"`

Then, replace header.h to the instruction that you want to include.



Advantages of RIS:

- Smaller binary size
- Less memory usage (Usually stack)

Advantages of CIS:

- Developer may use less amount of code



## Documentation

----

Headers:

- Necessary Headers (Need to be included in main.cpp)
  - `microv5/settings.h`
    - This file contains setting data that system functions may depend on.
  - `microv5/devlist.h`
    - This file contains devices information, such as motor or sensor object.
- Optional Headers (Both included in RIS and CIS) (C: Only CIS has this function)
  - `display.h`
    - `void dispSetLine(int specifiedLine, std::string content)`
      - This sets line on the Vex V5 Brain LCD.
    - C: `void dispPrint(std::string content)`
      - This adds text to next line.
    - C: `void dispClear()`
      - This clears the Vex V5 Brain LCD.
    - C: `void dispSetPrintedLineTo(int lineNum)`
      - This sets the display printing line number.
  - `motor.h`
    - `void motorRun(pros::Motor specifiedMotor, int speed)`
      - This runs motor to specified speed.
    - C: `void motorRunMultiple(pros::Motor specifedMotors[], int motorCounts, int speed)`
      - This runs multiple motors at once.
    - C: `void motorRunReverse(pros::Motor specifedMotor, int speed)`
      - This runs the motor in reverse direction.
    - C: `void motorRunReverseMultiple(pros::Motor specifiedMotors[], int motorCounts, int speed)`
      - This runs multiple motors at once in reverse direction.
  - `typeconvert.h`
    - `std::string convertToString(int toConvert)`
      - This convert the data type integer to std::string.
    - `std::string convertToString(double toConvert)`
      - This convert the data type double to std::string.
    - `std::string convertToString(char toConvert)`
      - This convert the data type char to std::string.
    - `int convertToInt(std::string integer)`
      - This parses std::string to int
    - `std::string stringJoin(std::vector<int> vect, std::string separator)`
      - This joins all vector elements in integer type into one single string with specified separator.
    - `std::string stringJoin(std::vector<std::string> vect, std::string separator)`
      - This joins all vector elements in string type into one single string with specified separator.
    - `std::vector<int> stringSplitToInt(std::string s, std::string separator)`
      - This splits string and parse them into int, then change to the vector type.
    - `std::vector<std::string> stringSplitToString(std::string s, std::string separator)`
      - This splits string, then change to the vector type.
  - `sensors.h`
    - Working in progress
  - C: `remotecontrol.h`
    - Working in progress
  - `files.h`
    - `std::string fReadStringFromFile(std::string fileName)`
      - This reads string data from the specified file
    - `int fWriteStringToFile(std::string fileName, std::string fileContent)`
      - This writes given string to specific text file inside the SD card, then returns the exit code. (0=Success)
    - `bool fFileExists(std::string fileName)`
      - This returns true if file exists. Returns false otherwise.
    - C: `fRenameFile(std::string original, std::string renameTo)`
      - This renames file.

