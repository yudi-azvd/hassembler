#include <cctype>
#include <exception>

#include "../include/parseline.h"
#include "../include/errors.h"

std::ostream &operator<<(std::ostream& os, const LineAndItsTokens& line) {
  std::string tokens = "";
  for(auto token : line.tokens)
    tokens.append("\"" + token + "\", ");
  return os << "\"" << line.line << "\"" << ", {" << tokens << "}";
}


std::vector<std::string> parseLine(std::string line) {
  int labelIndex = 0, operationIndex = 0, operand1Index = 0, operand2Index = 0;
  bool labelFound = false;
  std::vector<std::string> tokens;
  std::string label = "", operation = "", operand1 = "", operand2 = "";

  // encontrar label 
  label = findLabel(line);

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


std::string findLabel(std::string line) {
  char c;
  int i, labelIndex = 0;
  bool labelFound = false;
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

  // erro sintático
  // ++i; // pra ir pra depois do ':'
  // for (; i < line.length(); i++) {
  //   if (line[i] == ':' && labelFound) {
  //     throw SyntaticError("two labels in the same line");
  //   }
  // }
  
  return label;
}


void validateLabel(std::string label) {
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
