#ifndef FIRSTPASS_H_INCLUDED
#define FIRSTPASS_H_INCLUDED


#include "assembler/scanner/scanner.h"
#include "assembler/assemblydata.h"
#include "parser.h"


class FirstPass {
public:
  FirstPass() {};

  ~FirstPass() {};

  FirstPass(AssemblyData* assemblyData);

  void run();

private:
  void runOn(Source* source);

  void runOn(Line line);

  AssemblyData* assemblyData = nullptr;

  Source* source;

  Line line;

  Parser parser;

  int positionCounter;

  int lineCounter;

  int textSectionSize;

  int dataSectionSize;

  std::vector<std::string> tokens;

};


#endif // FIRSTPASS_H_INCLUDED
