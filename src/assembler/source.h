#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED

#include <iostream>
#include <vector>

#include "line.h"


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

  std::vector<Line> getLines();

  std::string getLineContentAt(int index);

private:
  bool _dataSectionComesFirst = false;

  int dataSectionLine = 0;

  int textSectionLine = 0;

  std::string modulename = "";

  std::vector<Line> lines;

/*
  // Só está definido quando é compileOnly=true,
  // é o nome do arquivo objeto.
  std::string outputObjetctFilename;


  std::string inputFilename;
  SymbolsTable symbolsTable;
  UsageTable usageTable;
  DefinitionsTable definitionsTable;
  ObjectCode objectCode;
  RelocationInformation relocInfo;
*/
};



#endif // SOURCE_H_INCLUDED

