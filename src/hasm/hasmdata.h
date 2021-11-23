#ifndef HASMDATA_H_INCLUDED
#define HASMDATA_H_INCLUDED

#include <iostream>
#include <vector>

#include "hasmparameters.h"
#include "assembler/assemblydata.h"


class HasmData {
public:
  HasmData(HasmParameters params);

  ~HasmData();

  AssemblyData* getAssemblyData();

  std::vector<std::string> getFilenames();

  void addSource(std::vector<std::string> source, std::string filename="");

  bool mustLink();

private:
  AssemblyData* assemblyData = nullptr;

  // LinkerData* LinkerData = nullptr;

  std::vector<std::string> inputFilenames;

  std::string outputFilename;

  bool _mustLink;
};


#endif // HASMDATA_H_INCLUDED
