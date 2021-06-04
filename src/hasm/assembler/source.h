#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED

#include <iostream>
#include <vector>

#include "util/definitionstable.hpp"
#include "util/usagetable.h"
#include "util/symbolstable.h"
#include "line.h"


/**
 * Representação interna do conteúdo de um arquivo fonte
 * e talvez alguns meta dados.
 */
class Source {
public:
  Source(std::vector<std::string> source, std::string filename="");

  ~Source();

  void setDataSectionComesFirst(bool comesFirst);

  bool dataSectionComesFirst();

  void setDataSectionLine(int line);

  int getDataSectionLine();

  void setTextSectionLine(int line);

  int getTextSectionLine();

  void setModulename(std::string name);

  std::string getModulename();

  bool hasModule();

  std::string getInputfilename();

  std::vector<Line> getLines();

  void disableLine(int line);

  std::string getLineContentAt(int index);

  DefinitionsTable* getDefinitionsTable();

  UsageTable* getUsageTable();

  SymbolsTable* getSymbolsTable();

  friend std::ostream& operator<<(std::ostream& os, const Source& s);

private:
  bool _dataSectionComesFirst = false;

  int dataSectionLine = 0;

  int textSectionLine = 0;

  std::string modulename = "";

  std::string inputFilename;

  std::vector<Line> lines;

  DefinitionsTable definitionsTable;

  UsageTable usageTable;

  SymbolsTable symbolsTable;

/*
  // Só está definido quando é compileOnly=true,
  // é o nome do arquivo objeto.
  std::string outputObjetctFilename;


  SymbolsTable symbolsTable;
  ObjectCode objectCode;
  RelocationInformation relocInfo;
*/
};



#endif // SOURCE_H_INCLUDED

