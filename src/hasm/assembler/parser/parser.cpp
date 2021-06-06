#include "parser.h"


void Parser::runOn(std::vector<std::string> tks) {
  tokens = tks;
  clear();
  parse();
}


std::string Parser::getLabel() {
  return label;
}


std::string Parser::getOperation() {
  return operation;
}


std::string Parser::getOperand1() {
  return operand1;
}


std::string Parser::getOperand2() {
  return operand2;
}


void Parser::parse() {
  if (tokens.size() == 0)
    return;
  findLabel();
  findOperation();
  findOperands();
}


void Parser::findLabel() {
  label.clear();

  size_t colonIndex;
  for (colonIndex = 0; colonIndex < tokens.size(); ++colonIndex) {
    if (tokens[colonIndex] == LABEL_TOKEN) {
      break;
    }
  }

  if (colonIndex == 0 || colonIndex == tokens.size()) {
    // Só vai dar certo nos testes. Doctest só pega erro que
    // é exceção std::exception.

    // throw AssemblyError("", 0, "missing label before ':'");
    callbackErrorFunction("missing label before ':'");
    label.clear();
    return;
  }

  labelIndex = colonIndex-1;
  label = tokens[labelIndex];
}


void Parser::findOperation() {
  operation.clear();

  if (label.empty()) {
    operationIndex = 0;
    operation = tokens[operationIndex];
    return;
  }

  bool thereIsNoOperation = labelIndex + 2 >= tokens.size();
  if (thereIsNoOperation) {
    operation.clear();
    return;
  }

  operationIndex = labelIndex + 2;
  operation = tokens[operationIndex];
}


// Talvez seja mehor separar em findOperand1 e 2
void Parser::findOperands() {
  operand1.clear();
  operand2.clear();

  bool labelExists = !label.empty();
  bool labelIsAloneInLine = tokens.size() == 2; // {"label", ":"}
  if (labelExists && labelIsAloneInLine) {
    return;
  }

  bool thereIsNoFirstOperand = operationIndex + 1 >= tokens.size();
  if (thereIsNoFirstOperand)
    return;

  operand1 = tokens[operationIndex + 1];

  bool thereIsNoSecondOperand = operationIndex + 2 >= tokens.size();
  if (thereIsNoSecondOperand)
    return;

  // e se o separador não for uma vírgula????
  if (tokens[operationIndex + 2] == ",") {
    operand2 = tokens[operationIndex + 3];
    return;
  }

  operand2 = tokens[operationIndex + 2];
}


void Parser::setCallbackErrorFunction(
  std::function<void(std::string)> callback
) {
  callbackErrorFunction = callback;
}



// talvez não seja necessário
void Parser::clear() {
  labelIndex = 0;
  operationIndex = 0;
}
