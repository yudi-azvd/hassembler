#include "linker.hpp"

Linker::Linker(std::vector<std::string> fns) {
  filenames = fns;
}


void Linker::link() {
  getFilesContents();

  correctionFactorTable = createCorrectionFactorTable(objectCodes);
  globalDefinitionsTable = createGlobalDefinitionsTable(definitionsTables);

  int moduleCounter = 0;
  for (auto objectCode : objectCodes) {
    adjustUsagesInObjectCodeWithGlobalDefinitionsTable(moduleCounter);
    // adjustAddressesInObjectCode(moduleCounter);
    adjustRelativeAddressesInObjectCode(moduleCounter);

    moduleCounter++;
  }

  finalObjectCode = alignObjectCodes(objectCodes);

  // printData();
  if (errors.size() > 0) {
    std::cout << ns_linker::vectorToString(errors) << std::endl;
  }
  else {
    generateOutput();
  }
}


void Linker::getFilesContents() {
  for (auto filename : filenames) {
    readFileContent(filename);
    extractModulename();
    extractRelocationInformation();
    extractUsageTable();
    extractDefinitionsTable();
    extractObjectCode();
  }
}


void Linker::readFileContent(std::string filename) {
  std::string line;
  std::fstream infile(filename);
  std::vector<std::string> fileContent;

  if (!infile.is_open()) {
    errors.push_back("Arquivo não encontrado: " + filename);
  }

  while (std::getline(infile, line)) {
    // Tem que fazer trim da linha
    fileContent.push_back(line);
  }

  infile.close();

  filesContents.push_back(fileContent);
}


void Linker::extractModulename() {
  int firstLine = 0;
  std::string line, modulename;
  auto fileContent = filesContents.back();

  line = fileContent[firstLine];
  if (line[0] != 'H') {
    errors.push_back("Módulo " + modulesnames.back() + "não obedece"
      "às regras de formatação de cabeçalho");
  }
  else {
    modulename = line.substr(2);
    modulesnames.push_back(modulename);
  }
}


void Linker::extractRelocationInformation() {
  char recInfo;
  std::vector<int> relocationInfo;
  std::string name = "", substr = "";
  auto fileContent = filesContents.back();
  std::stringstream ss;

  // é só pegar a terceira linha
  for (auto line : fileContent) {
    if (line[0] != 'R')
      continue;

    substr = line.substr(2);
    ss << substr;

    while (!ss.eof()) {
      ss >> recInfo;
      recInfo -= '0';
      relocationInfo.push_back(recInfo);
    }

    relocationInfo.pop_back(); // remover -48 no final devido ao '\0'-'0'
    relocationInfo.shrink_to_fit();
    relocations.push_back(relocationInfo);
    break;
  }
}


void Linker::extractObjectCode() {
  int code;
  std::vector<int> objectCode;
  std::string name = "", substr = "";
  auto fileContent = filesContents.back();
  std::stringstream ss;

  // é só pegar a última linha
  for (auto line : fileContent) {
    if (line[0] != 'T')
      continue;
    
    substr = line.substr(2);
    substr.pop_back(); // remover um espaço adicional na linha
    ss << substr;

    while (!ss.eof()) {
      ss >> code;
      objectCode.push_back(code);
    }

    objectCode.shrink_to_fit();
    objectCodes.push_back(objectCode);
  }
}


void Linker::extractUsageTable() {
  int position = 0;
  std::string name = "", substr = "";
  auto fileContent = filesContents.back();
  UsageTable usageTable;
  std::stringstream ss;

  // é só ler a partir da terceira linha
  for (auto line : fileContent) {
    if (line[0] != 'U')
      continue;
    
    substr = line.substr(2);
    ss << substr;
    ss >> name >> position;
    ss.clear();
    
    usageTable.add(name, position);
  }

  usageTables.push_back(usageTable);
}


void Linker::extractDefinitionsTable() {
  int position = 0;
  std::string name = "", substr = "";
  auto fileContent = filesContents.back();
  DefinitionsTable definitionsTable;
  std::stringstream ss;

  for (auto line : fileContent) {
    if (line[0] != 'D')
      continue;
    
    substr = line.substr(2);
    ss << substr;
    ss >> name >> position;
    ss.clear();
    
    definitionsTable.add(name, position);
  }

  definitionsTables.push_back(definitionsTable);
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
  int correctionFactor;
  DefinitionsTable globalTable;

  int moduleCounter = 0;
  for (auto& defsTable : definitionsTables) {
    correctionFactor = correctionFactorTable.getSizeOf(
      modulesnames[moduleCounter]);
    for (auto& definition : defsTable.getTable()) {
      globalTable.add(definition.first, definition.second + correctionFactor);
    }
    moduleCounter++;
  }

  return globalTable;
}


void Linker::adjustUsagesInObjectCodeWithGlobalDefinitionsTable(int moduleCounter) {
  auto modulename = modulesnames[moduleCounter];
  auto& currentObjectCode = objectCodes[moduleCounter];
  auto ut = usageTables[moduleCounter];

  for (auto& usage : ut.getTable()) {
    int position = usage.first;
    auto name = usage.second;
    int correction = globalDefinitionsTable.getPositionOf(name);
    currentObjectCode[position] += correction;
  }

  // std::cout << "terminou mod: " << moduleCounter << std::endl;
}


void Linker::adjustAddressesInObjectCode(int moduleCounter) {
  auto modulename = modulesnames[moduleCounter];

}


void Linker::adjustRelativeAddressesInObjectCode(int moduleCounter) {
  auto modulename = modulesnames[moduleCounter];
  auto& currentObjectCode = objectCodes[moduleCounter];
  auto& currentRelocationInformation = relocations[moduleCounter];
  int correctionFactor = correctionFactorTable.getSizeOf(modulename);

  const int relativeAddress = 1;
  int positionCounter = 0;
  for (auto reloc : currentRelocationInformation) { 
    if (reloc == relativeAddress) {
      currentObjectCode[positionCounter] += correctionFactor;
    }

    positionCounter++;
  }
}


std::vector<int> Linker::getFinalObjectCode() {
  return finalObjectCode;
}


void Linker::generateOutput() {
  auto outFilename = filenames[0];
  int dotIndex = 0;

  for (dotIndex = outFilename.size()-1; dotIndex >= 0; dotIndex--) {
    if (outFilename[dotIndex] == '.')
      break;
  }

  outFilename.insert(dotIndex, "_ligado");
  std::fstream outputFile;
  outputFile.open(outFilename, std::ios::out);

  std::stringstream ss;

  for (auto code : finalObjectCode) {
    ss << code << " ";
  }

  outputFile << ss.str();
  outputFile.close();
}


void Linker::printData() {
  std::cout << "CORR FACTOR" << std::endl;
  std::cout << correctionFactorTable.toString() << std::endl;
  std::cout << "\nMODULE NAMES" << std::endl;
  std::cout << ns_linker::vectorToString(modulesnames) << std::endl;
  std::cout << "RELOCATION INFO" << std::endl;
  for (auto recInfo : relocations) 
    std::cout << recInfo.size() << " | " << ns_linker::vectorToString(recInfo) << std::endl;
  std::cout << "\nUSAGE TABLES" << std::endl;
  for (auto ut : usageTables) {
    std::cout << ut << std::endl;
  }
  std::cout << "\nDEFINITIONS TABLES" << std::endl;
  for (auto dt : definitionsTables) {
    std::cout << dt << std::endl;
  }
  std::cout << "\nOBJECT CODE" << std::endl;
  for (auto oc : objectCodes) 
    std::cout << oc.size() << " | " << ns_linker::vectorToString(oc) << std::endl;
  
  std::cout << ns_linker::vectorToString(errors) << std::endl;

}