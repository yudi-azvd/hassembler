#ifndef ASSEMBLYDATA_INCLUDED
#define ASSEMBLYDATA_INCLUDED

#include <iostream>
#include <vector>

#include "assembler/source.h"
#include "assembler/assemblyerror.h"


class AssemblyData {
public:
  AssemblyData();

  ~AssemblyData();

  void addSource(std::vector<std::string> source, std::string filaname="");

  size_t getSourcesSize();

  std::vector<Source*> getSources();

  Source* getNthSource(int index);

  void addError(std::string filename, int line, std::string message);

  std::vector<AssemblyError> getErrors();

  std::vector<std::string> getInputFilenames();

private:
  std::vector<Source*> sources;

  std::vector<AssemblyError> errors;
};


#endif // ASSEMBLYDATA_INCLUDED

