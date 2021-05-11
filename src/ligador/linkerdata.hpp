#ifndef LINKERDATA_H_INCLUDED
#define LINKERDATA_H_INCLUDED

#include <iostream>
#include <vector>

#include "usagetable.hpp"
#include "definitionstable.hpp"


struct LinkerData {
  UsageTable usageTable;
  DefinitionsTable definitionsTable;
  std::vector<std::string> objectCode;
};


#endif // LINKERDATA_H_INCLUDED