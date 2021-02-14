#include "main.h"
#include <string.h>
#include <fstream>
#include <stdio.h>

std::string fReadStringFromFile(std::string fileName) {
  FILE* read_file = fopen(fileName.c_str(), "r");
  if (read_file){
    fseek(read_file, 0, SEEK_END);
    size_t len = ftell(read_file);
    fseek(read_file, 0, SEEK_SET);
    std::string contents(len+1, '\0');
    fread(&contents[0], 1, len, read_file);
    fclose(read_file);
    return contents;
  }
}

int fWriteStringToFile(std::string fileName, std::string fileContent ) {
  FILE* write_file = fopen(fileName.c_str(), "w");
  fputs(fileContent.c_str(), write_file);
  fclose(write_file);
  return 1;
}

bool fFileExists(std::string fileName) {
  if (FILE *file=fopen(fileName.c_str(), "r")) {
    fclose(file);
    return true;
  }
  else{
    return false;
  }
}

int fRenameFile(std::string original, std::string renameTo) {
  if (rename(original.c_str(), renameTo.c_str()) != 0) {
    return -1;
  }
  else{
    return 1;
  }
  return 0;
}
