#ifndef LINKER_H_INCLUDED
#define LINKER_H_INCLUDED

#include <iostream>
#include <vector>

#include "correctionfactortable.hpp"
#include "definitionstable.hpp"

class Linker {
public:
  Linker(std::vector<std::string> filenames);

  ~Linker() { }

  void link();

  std::vector<int> alignObjectCodes(std::vector<std::vector<int>> objectCodes);
  
  CorrectionFactorTable createCorrectionFactorTable(std::vector<std::vector<int>> objectCodes);

  DefinitionsTable createGlobalDefinitionsTable(std::vector<DefinitionsTable> definitionsTables);

  void adjustUsageTable(/* globalDefinitionsTable */);

  void adjustAddressesInObjectCode(/* correctionFactor */);

  void adjustRelativeAddresses(/* correctionFactor */);

  std::vector<int> getFinalObjectCode();

private:

  void readFile(std::string filename);

  void generateOutput();

  std::vector<std::string> filenames;

  std::vector<std::string> modulesnames;

  CorrectionFactorTable correctionFactorTable;

  std::vector<DefinitionsTable> definitionsTables;

  DefinitionsTable globalDefinitionsTable;

  std::vector<int> finalObjectCode;

  std::vector<std::vector<int>> objectCodes;

};

#endif // LINKER_H_INCLUDED