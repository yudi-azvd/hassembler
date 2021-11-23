#ifndef HASMPARAMETERS_H_INCLUDED
#define HASMPARAMETERS_H_INCLUDED

#include <iostream>
#include <vector>

struct HasmParameters {
  bool isCompileOnly = false;

  bool dumpHasmData = false;

  std::vector<std::string> filenames;

  std::string outputFilename;

  // ~HasmParameters() {}
};


#endif // HASMPARAMETERS_H_INCLUDED
