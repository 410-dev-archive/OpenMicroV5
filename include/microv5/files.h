#include "main.h"

class MFiles {
public: std::string readStringFromFile(std::string fileName);
public: int writeStringToFile(std::string fileName, std::string fileContent);
public: bool fileExists(std::string fileName);
public: int renameFile(std::string original, std::string renameTo);
};
