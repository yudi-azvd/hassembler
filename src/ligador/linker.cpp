#include "linker.hpp"

Linker::Linker(std::vector<std::string> fns) {
  filenames = fns;
}


void Linker::link() {
  finalObjectCode = alignObjectCodes(objectCodes);
  correctionFactorTable = createCorrectionFactorTable(objectCodes);
  globalDefinitionsTable = createGlobalDefinitionsTable(definitionsTables);

  int counter = 0;
  for (auto objectCode : objectCodes) {
    adjustUsageTable(/* globalDefinitionsTable */);
    adjustAddressesInObjectCode(/* correctionFactor */);
    adjustRelativeAddresses(/* correctionFactor */);

    counter++;
  }

  generateOutput();
}


std::vector<int> Linker::alignObjectCodes(std::vector<std::vector<int>> objectCodes) {
  std::vector<int> objectCode;
  for (auto oc : objectCodes) {
    for (auto code : oc) {
      objectCode.push_back(code);
    }
  }

  return objectCode;
}


CorrectionFactorTable Linker::createCorrectionFactorTable(
  std::vector<std::vector<int>> objectCodes
) {
  CorrectionFactorTable correctionFactorTable;
  int counter = 0;
  for (auto objectCode : objectCodes) {
    correctionFactorTable.add(modulesnames[counter], objectCode.size());
    counter++;
  }

  return correctionFactorTable;
}


DefinitionsTable Linker::createGlobalDefinitionsTable(
  std::vector<DefinitionsTable> definitionsTables
) {
  DefinitionsTable globalTable;

  return globalTable;
}


void Linker::adjustUsageTable(/* globalDefinitionsTable */) {

}


void Linker::adjustAddressesInObjectCode(/* correctionFactor */) {

}


void Linker::adjustRelativeAddresses(/* correctionFactor */) {

}


std::vector<int> Linker::getFinalObjectCode() {
  return finalObjectCode;
}


void Linker::generateOutput() {

}