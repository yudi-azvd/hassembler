#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include <vector>
#include <functional>

#include "assembler/assemblyerror.h"


/**
 * Realiza a análise sintática de uma linha.
 *
 * Sobre ponteiros para funções:
 * https://www.learncpp.com/cpp-tutorial/function-pointers/
 */
class Parser {
public:
  void runOn(std::vector<std::string> tokens);

  void setCallbackErrorFunction(
    std::function<void(std::string)> callbackErrorFunction);

  std::string getLabel();

  std::string getOperation();

  std::string getOperand1();

  std::string getOperand2();

private:
  const std::string LABEL_TOKEN = ":";

  void clear();

  void parse();

  void findLabel();

  void findOperation();

  void findOperands();

  std::function<void(std::string)> callbackErrorFunction;

  std::vector<std::string> tokens;

  std::string label;

  size_t labelIndex = 0;

  std::string operation;

  size_t operationIndex = 0;

  std::string operand1;

  std::string operand2;
};


#endif // PARSER_H_INCLUDED
