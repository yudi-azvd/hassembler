#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include <vector>

#include "assembler/assemblydata.h"


/**
 * Realiza a análise sintática de uma linha.
 */
class Parser {
public:
  void runOn(std::vector<std::string> tokens);

  std::string getLabel();

  std::string getOperation();

  std::string getOperand1();

  std::string getOperand2();

  void setAssemblyData(AssemblyData* assemblyData);

  void setLineCounter(int lineCounter);

  void setFilename(std::string filename);
private:
  AssemblyData* assemblyData;

  std::string filename;

  int lineCounter;

  const std::string LABEL_TOKEN = ":";

  void clear();

  void parse();

  void findLabel();

  void findOperation();

  void findOperands();

  std::vector<std::string> tokens;

  std::string label;

  size_t labelIndex = 0;

  std::string operation;

  size_t operationIndex = 0;

  std::string operand1;

  std::string operand2;
};


#endif // PARSER_H_INCLUDED
