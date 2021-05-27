#ifndef HASMPARAMETERS_H_INCLUDED
#define HASMPARAMETERS_H_INCLUDED

#include <iostream>
#include <vector>

struct HasmParameters {
  bool isCompileOnly = false;

  std::vector<std::string> fileNames;

  std::string outputFileName;

  // ~HasmParameters() {}
};


#endif // !HASMPARAMETERS_H_INCLUDED
