#ifndef HASMDATA_H_INCLUDED
#define HASMDATA_H_INCLUDED

#include <iostream>
#include <vector>

#include "hasmparameters.h"
#include "assembler/assemblerdata.h"


class HasmData {
public:
  HasmData(HasmParameters params);

  ~HasmData();

  bool mustLink();

private:
  AssemblerData* assemblerData;

  // LinkerData* LinkerData;

  std::string outputFilename;

  bool _mustLink;
};


#endif // HASMDATA_H_INCLUDED
