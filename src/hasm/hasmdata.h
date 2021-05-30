#ifndef HASMDATA_H_INCLUDED
#define HASMDATA_H_INCLUDED

#include <iostream>
#include <vector>

#include "util/correctionfactortable.hpp"
#include "hasmparameters.h"

class Source;

class HasmData {
public:
  HasmData(HasmParameters params);

  ~HasmData();

  bool mustLink();

private:
  std::vector<Source> sources;

  std::string outputFilename;

  bool _mustLink;
};


/**
 * Representação interna do conteúdo de um arquivo fonte
 * e talvez alguns meta dados.
 */
class Source {
public:
  std::string getModulename();

  std::string getOutputFilename();

  bool isModule();

private:
  std::string modulename;

  std::string inputFilename;

  // Só está definido quando é compileOnly=true,
  // é o nome do arquivo objeto.
  std::string outputObjetctFilename;

  bool _isModule;
/*
  FileContent fileContent;

  SymbolsTable symbolsTable;
  UsageTable usageTable;
  DefinitionsTable definitionsTable;
  ObjectCode objectCode;
  RelocationInformation relocInfo;
*/
};


#endif // HASMDATA_H_INCLUDED
