#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED

#include <iostream>
#include <vector>

#include "line.h"
#include "util/definitionstable.hpp"


/**
 * Representação interna do conteúdo de um arquivo fonte
 * e talvez alguns meta dados.
 */
class Source {
public:
  Source(std::vector<const char*> lines);

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

  void addToDefinitionsTable(std::string name, int pos);

  DefinitionsTable getDefinitionsTable();

  friend std::ostream& operator<<(std::ostream& os, const Source& s);

private:
  bool _dataSectionComesFirst = false;

  int dataSectionLine = 0;

  int textSectionLine = 0;

  std::string modulename = "";

  std::string inputFilename;

  std::vector<Line> lines;

  DefinitionsTable definitionsTable;

/*
  // Só está definido quando é compileOnly=true,
  // é o nome do arquivo objeto.
  std::string outputObjetctFilename;


  SymbolsTable symbolsTable;
  UsageTable usageTable;
  ObjectCode objectCode;
  RelocationInformation relocInfo;
*/
};



#endif // SOURCE_H_INCLUDED

