#ifndef ASSEMBLYOPTIONS_H_INCLUDED
#define ASSEMBLYOPTIONS_H_INCLUDED

#include <iostream>
#include <vector>

struct AssemblyOptions {
  bool isCompileOnly = false;

  std::vector<std::string> fileNames;
  
  std::string outputFileName;

  // ~AssemblyOptions() {}
};


#endif // !ASSEMBLYOPTIONS_H_INCLUDED