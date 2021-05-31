#ifndef LINKER_H_INCLUDED
#define LINKER_H_INCLUDED

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <sstream>

#include "util/correctionfactortable.hpp"
#include "util/definitionstable.hpp"
#include "util/usagetable.h"
#include "util/util.h"


class Linker {
public:
  Linker(std::vector<std::string> filenames);

  ~Linker() { }

  void link();

  std::vector<int> alignObjectCodes(std::vector<std::vector<int>> objectCodes);

  CorrectionFactorTable createCorrectionFactorTable(std::vector<std::vector<int>> objectCodes);

  DefinitionsTable createGlobalDefinitionsTable(std::vector<DefinitionsTable> definitionsTables);

  void adjustGlobalDefinitionsTable();

  void adjustUsagesInObjectCodeWithGlobalDefinitionsTable(int moduleCounter);

  void adjustAddressesInObjectCode(int moduleCounter);

  void adjustRelativeAddressesInObjectCode(int moduleCounter);

  std::vector<int> getFinalObjectCode();

private:
  void getFilesContents();

  // Acrescenta um fileContent em filesContents
  void readFileContent(std::string filename);

  void extractModulename();

  void extractRelocationInformation();

  void extractUsageTable();

  void extractDefinitionsTable();

  void extractObjectCode();

  void generateOutput();

  void printData();

  std::vector<std::string> filenames;

  std::vector<std::vector<std::string>> filesContents;

  std::vector<std::string> modulesnames;

  CorrectionFactorTable correctionFactorTable;

  std::vector<DefinitionsTable> definitionsTables;

  std::vector<UsageTable> usageTables;

  DefinitionsTable globalDefinitionsTable;

  std::vector<std::vector<int>> relocations;

  std::vector<int> finalObjectCode;

  std::vector<std::vector<int>> objectCodes;

  std::vector<std::string> errors;
};

#endif // LINKER_H_INCLUDED
