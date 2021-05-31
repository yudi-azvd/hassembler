#ifndef ASSEMBLERDATA_INCLUDED
#define ASSEMBLERDATA_INCLUDED

#include <iostream>
#include <vector>

#include "assembler/source.h"


class AssemblerData {
public:
  AssemblerData();

  ~AssemblerData();

  void addSource(std::vector<const char*> source);

  size_t getSourcesSize();

  std::vector<Source*> getSources();

  Source getNthSource(int index);

private:
  std::vector<Source*> sources;
};


#endif // ASSEMBLERDATA_INCLUDED

