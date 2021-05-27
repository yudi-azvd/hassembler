#ifndef COMMANDLINEPARSER_H_INCLUDED
#define COMMANDLINEPARSER_H_INCLUDED

#include <iostream>
#include <exception>
#include <algorithm>

#include "assemblyoptions.h"

class CommandLineParser {
public:
  CommandLineParser();

  CommandLineParser(int argc, const char* commandLineArguments[]);

  ~CommandLineParser();

  AssemblyOptions run();

private:
  const std::string OUTPUT_FILE_NAME_FLAG = "-o";

  const std::string COMPILE_ONLY_FLAG = "-c";

  int argumentsCount;

  std::vector<std::string> arguments;

  AssemblyOptions assemblyOptions;

  bool hasMultipleInputFiles();

  void checkForOuputFileNameFlag();

  void checkForCompileOnlyFlag();

  void throwIfThereAreMultipleFilesAndOutputFlag();

  void getFileNames();

  void throwIfOutputNameEqualsInputName();
};

#endif // COMMANDLINEPARSER_H_INCLUDED
