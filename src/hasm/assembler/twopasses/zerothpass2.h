#ifndef ZEROTHPASS2_H_INCLUDED
#define ZEROTHPASS2_H_INCLUDED

#include <algorithm>

#include "assembler/scanner/scanner.h"
#include "assembler/assemblydata.h"
#include "util/util.h"

/**
 * Faz detecção de módulos lidando com as diretivas BEGIN, END, PUBLIC, EXTERN.
 *
 * Falha de design: não cumpre o Single Responsability Principle. Em outro ponto
 * do Hassembler, vão existir funções que lidam com diretivas. Quando novas
 * diretivas forem introduzidas, EQU por exemplo, vão ser duas classes que devem
 * sofrer alterações: ZerothPass2 e outra aí.
 *
 * O que notei agora é que existem dois tipos de diretivas:
 * 1 - BEGIN, END, PUBLIC, EXTERN, EQU, MACRO?, IF?
 *
 * 2 - CONST, SPACE, SPACE 10, STRING (no futuro)
 */
class ZerothPass2 {
public:
  ZerothPass2();

  ZerothPass2(AssemblyData* ad);

  ~ZerothPass2();

  void run();

private:
  void runOn(Source* source);

  AssemblyData* assemblyData;

  Source* source;

  void runOnLine(Line line);

  void handleError(const AssemblyError& e);

  void handlePublicDirectiveIfItExists();

  void handleBeginDirectiveIfItExists();

  void handleEndDirectiveIfItExists();

  void handleExternDirectiveIfItExists();

  void checkForBeginAndEndMatch();

  bool found(std::string directive);

  DefinitionsTable* definitionsTable;

  UsageTable* usageTable;

  int lineCounter;

  bool lineHasBeginDirective;

  bool lineHasEndDirective;

  bool lineHasPublicDirective;

  bool lineHasExternDirective;

  bool sourceHasEndDirective = false;

  std::vector<std::string> tokens;

  std::vector<std::string> lowerCasedTokens;

  std::vector<std::string>::iterator iter;
};


#endif // ZEROTHPASS2_H_INCLUDED
