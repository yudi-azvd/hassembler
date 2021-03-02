#include <cctype>

#include "../include/parseline.h"

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
  for (int i = 0; i < line.length(); i++) {
    if (line[i] == ':' && !labelFound) {
      labelFound = true;
      labelIndex = i-1; // desconsiderar ':'

      // tem que verificar se tem _ ou outros chars válidos.
      while (std::isalpha(line[labelIndex]) || std::isdigit(line[labelIndex]) && labelIndex >= 0) {
        char c = line[labelIndex--];
        label.insert(0, 1, c);
      }
      
      // label mal escrito vai dar ruim!!!
      /**
       * if (label[0] is not letter) {
       *    throw new LexicalError
       * }
      */
    }
  }

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

      // tem que verificar se tem _ ou outros chars válidos.
      // isValidCharForLabel(line[labelIndex])
      while (std::isalpha(line[labelIndex]) || std::isdigit(line[labelIndex]) && labelIndex >= 0) {
        c = line[labelIndex--]; // c não é necessário!
        label.insert(0, 1, c);
      }
      
      // label mal escrito vai dar ruim!!!
      /**
       * if (label[0] is not letter) {
       *    throw new LexicalError
       * }
      */

      break;
    }
  }

  // erro sintático
  for (; i < line.length(); i++) {
    // if found another label && labelFound 
    //    throw new TwoLabelsSameLineExeception
  }
  
  return label;
}
