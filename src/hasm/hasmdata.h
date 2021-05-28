#ifndef HASMDATA_H_INCLUDED
#define HASMDATA_H_INCLUDED

#include <iostream>

#include "util/correctionfactortable.hpp"
#include "hasmparameters.h"

class HasmData {
public:
  HasmData(HasmParameters params);

private:
/*
  vector<Source>
  string outputFilename = params.outputFilename
  bool mustLink = !params.isCompileOnly
*/


};

/*

class Source {
  bool isModule
  string inputFilename
  string outputFilename
  string modulename;
  FileContent fileContent;
  SymbolsTable symbolsTable;
  UsageTable usageTable;
  DefinitionsTable definitionsTable;
  ObjectCode objectCode;
  RelocationInformation relocInfo;
}

*/

#endif // HASMDATA_H_INCLUDED
