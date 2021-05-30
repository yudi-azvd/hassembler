#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED

#include <iostream>
#include <vector>

#include "sourcecontent.h"


/**
 * Representação interna do conteúdo de um arquivo fonte
 * e talvez alguns meta dados.
 */
class Source {
public:
  Source(SourceContent& content);

  Source(std::vector<const char*> lines);

  ~Source();

  SourceContent& getContent();

  void setDataSectionComesFirst(bool comesFirst);

  bool dataSectionComesFirst();

  void setDataSectionLine(int line);

  int getDataSectionLine();

  void setTextSectionLine(int line);

  int getTextSectionLine();

private:
  bool _dataSectionComesFirst = false;

  int dataSectionLine = 0;

  int textSectionLine = 0;

  SourceContent sourceContent;

/*
  // Só está definido quando é compileOnly=true,
  // é o nome do arquivo objeto.
  std::string outputObjetctFilename;

  std::string modulename;

  std::string inputFilename;
  SymbolsTable symbolsTable;
  UsageTable usageTable;
  DefinitionsTable definitionsTable;
  ObjectCode objectCode;
  RelocationInformation relocInfo;
*/
};



#endif // SOURCE_H_INCLUDED

