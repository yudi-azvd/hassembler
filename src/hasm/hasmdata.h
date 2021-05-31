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

  bool mustLink();

private:
  AssemblyData* assemblyData;

  // LinkerData* LinkerData;

  std::string outputFilename;

  bool _mustLink;
};


#endif // HASMDATA_H_INCLUDED
