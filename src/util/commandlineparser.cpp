#include "commandlineparser.h"

CommandLineParser::CommandLineParser() { }


CommandLineParser::CommandLineParser(int argc, const char* argv[]) {
  constexpr int executableNameOffset = 1;
  std::vector<std::string> v(argv+executableNameOffset, argv + argc);
  assemblyOptions.fileNames = v;
}


CommandLineParser::~CommandLineParser() {}


AssemblyOptions CommandLineParser::getAssemblyOptions() {
  return assemblyOptions;
}