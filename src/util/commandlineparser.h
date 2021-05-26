#ifndef COMMANDLINEPARSER_H_INCLUDED
#define COMMANDLINEPARSER_H_INCLUDED

#include <iostream>

#include "assemblyoptions.h"

class CommandLineParser {
public:
  CommandLineParser();

  CommandLineParser(int argc, const char* commandLineArguments[]);

  ~CommandLineParser();

  AssemblyOptions getAssemblyOptions();

private:
  AssemblyOptions assemblyOptions;
};

#endif // COMMANDLINEPARSER_H_INCLUDED
