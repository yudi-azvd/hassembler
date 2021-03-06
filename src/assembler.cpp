#include <vector>

#include "../include/assembler.h"
#include "../include/errors.h"

std::ostream &operator<<(std::ostream& os, const LineAndItsTokens& line) {
  std::string tokens = "";
  for(auto token : line.tokens)
    tokens.append("\"" + token + "\", ");
  return os << "\"" << line.line << "\"" << ", {" << tokens << "}";
}


Assembler::Assembler() { 
  opcodeTable = {
    {"ADD", 1},
    {"SUB", 2},
    {"MUL", 3},
    {"DIV", 4},
    {"JMP", 5},
    {"JMPN", 6},
    {"JMPP", 7},
    {"JMPZ", 8},
    {"COPY", 9},
    {"LOAD", 10},
    {"STORE", 11},
    {"INPUT", 12},
    {"OUTPUT", 13},
    {"STOP", 14},
  };
} 


Assembler::~Assembler() { }


void Assembler::assemble(std::vector<std::string> sourceFileContent) {
  this->sourceFileContent = sourceFileContent; // tem cara de construtor

  runFirstPass();
  // sunSecondPass();
}


void Assembler::runFirstPass() {
  int positionCounter = 0;
  int lineCounter = 1;
  std::vector<std::string> tokens;
  std::string label, operation, operand1, operand2;
  std::string savedLabelForLater;

  for (std::string line : sourceFileContent) {
    // not necessarily length = 0
    // if line is empty: continue; lineCounter++;
    tokens = parseLine(line);
    // if tokens.size() == 0: continue; savedLabelForLater=label; lineCounter++; // linha vazia
    // if label?.size() == 0: continue; savedLabelForLater=label; lineCounter++; // linha vazia
    // doStuffWithTokens(tokens); // teste de unidade
    if (savedLabelForLater.length() > 0) {
      label = savedLabelForLater;
      savedLabelForLater = "";
    }
    else {
      label = tokens[0];
    }
    operation = tokens[1];
    operand1 = tokens[2];
    operand2 = tokens[3];

    // LABEL
    if (label.length() > 0) {
      bool labelFound = symbolTable.find(label) != symbolTable.end();
      if (!labelFound) {
        symbolTable[label] = positionCounter;
      }
      else {
        // throw error: símbolo redefinido
      }
    }

    // OPERATION 
    bool operationFound = opcodeTable.find(operation) != opcodeTable.end();
    if (operationFound) {
      // positionCounter += 
      // erro por número errado de operandos?
      positionCounter += 2; // numero de operandos ou tamanho da instrução
    }
    else {
      // procura na tabela de diretivas
      // Se achou:
      //   chama subrotina que executa a diretiva
      //   contador_posição = valor retornado pela subrotina
      // Senão: 
      //   Erro, operação não identificada
    }

    lineCounter++;
  }
} 


std::vector<std::string> Assembler::parseLine(std::string line) {
  // bool labelFound = false;
  // int labelIndex = 0, operationIndex = 0, operand1Index = 0, operand2Index = 0;
  std::string label = "", operation = "", operand1 = "", operand2 = "";
  std::vector<std::string> tokens;

  // encontrar label 
  label = findLabel(line);

  // while not comment 
  //    tokens.push(findNextTokenStarttingFrom());

  // operation = findOperation(line); // eu preciso verificar a existencia da operação?
  // encontrar operando 
  // i = label.length()+1 
  // procurar operandos a partir de i

  tokens.push_back(label);
  tokens.push_back(operation);
  tokens.push_back(operand1);
  tokens.push_back(operand2);
  
  return tokens;
}


std::string Assembler::findLabel(std::string line) {
  char c;
  bool labelFound = false;
  size_t i = 0;
  int labelIndex = 0;
  std::string label = "";

  for (i = 0; i < line.length(); i++) {
    if (line[i] == ':' && !labelFound) {
      labelFound = true;
      labelIndex = i-1; // desconsiderar ':'

      while (
        labelIndex >= 0 && 
        (line[labelIndex] != ' ' 
        || line[labelIndex] != '\t' 
        || line[labelIndex] == '_')
      ) {
        c = line[labelIndex--];
        label.insert(0, 1, c);
      }
      
      validateLabel(label);

      break;
    }
  }
  
  return label;
}


// retonar mais de um valor na função
// https://www.educative.io/edpresso/how-to-return-multiple-values-from-a-function-in-cpp17
std::string Assembler::findNextTokenStartingFrom(
  size_t start, 
  std::string line,
  int& tokenStartsAt
) {
  size_t i;
  char c;
  bool symbolStarted = false,
    isCommentDelimiter, isTokenDelimiter, isWhitespace;
  std::string symbol = ""; 

  for (i = start; i < line.length(); i++) {
    c = line[i];
    isCommentDelimiter = c == ';';
    isWhitespace = (c == ' ' || c == '\t');
    isTokenDelimiter = c == ':';

    if (isCommentDelimiter) {
      tokenStartsAt = symbolStarted 
        ? i-symbol.length() 
        : -1;
      return symbol;
    }

    if (!symbolStarted && isWhitespace) {
      continue;
    }

    if (symbolStarted && (isWhitespace || isTokenDelimiter)) {
      tokenStartsAt = i-symbol.length();
      return symbol;
    }

    if (!isWhitespace) {
      symbolStarted = true;
      symbol.push_back(c);

      if (isTokenDelimiter) {
        tokenStartsAt = i;
        return symbol;
      }
    }
  }

  tokenStartsAt = symbolStarted 
    ? i-symbol.length() 
    : -1;

  return symbol;
}

/**
 * CORRETO É CRIAR UMA LISTA PARA OS ERROS EM VEZ DE 
 * lançar uma excessão
 */
void Assembler::validateLabel(std::string label) {
  if (!std::isalpha(label[0]) && label[0] != '_') {
    throw LexicalError("invalid label: " + label);
  }

  bool isValidChar = true;
  for (auto c : label) {
    isValidChar = std::isalpha(c) || std::isdigit(c) || c == '_';
    if (!isValidChar) {
      throw LexicalError("invalid label: " + label);
    }
  }
}
