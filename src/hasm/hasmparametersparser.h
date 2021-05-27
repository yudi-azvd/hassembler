#ifndef HASMPARAMETERSPARSER_H_INCLUDED
#define HASMPARAMETERSPARSER_H_INCLUDED

#include <iostream>
#include <exception>
#include <algorithm>

#include "hasmparameters.h"

class HasmParametersParser {
public:
  HasmParametersParser();

  HasmParametersParser(int argc, const char* commandLineArguments[]);

  ~HasmParametersParser();

  HasmParameters run();

private:
  const std::string OUTPUT_FILE_NAME_FLAG = "-o";

  const std::string COMPILE_ONLY_FLAG = "-c";

  std::vector<std::string> arguments;

  HasmParameters assemblyParameters;

  bool hasMultipleInputFiles();

  void checkForOuputFileNameFlag();

  void checkForCompileOnlyFlag();

  void throwIfThereAreMultipleFilesAndOutputFlag();

  void getFileNames();

  void throwIfOutputNameEqualsInputName();
};

#endif // HASMPARAMETERSPARSER_H_INCLUDED
