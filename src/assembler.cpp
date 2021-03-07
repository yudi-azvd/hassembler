#include <vector>

#include "../include/assembler.h"
#include "../include/errors.h"


Assembler::Assembler() { 
  opcodeTable = {
    {"add", 1},
    {"sub", 2},
    {"mul", 3},
    {"div", 4},
    {"jmp", 5},
    {"jmpn", 6},
    {"jmpp", 7},
    {"jmpz", 8},
    {"copy", 9},
    {"load", 10},
    {"store", 11},
    {"input", 12},
    {"output", 13},
    {"stop", 14},
  };

  // opcodeTable = {
  //   {"ADD", 1},
  //   {"SUB", 2},
  //   {"MUL", 3},
  //   {"DIV", 4},
  //   {"JMP", 5},
  //   {"JMPN", 6},
  //   {"JMPP", 7},
  //   {"JMPZ", 8},
  //   {"COPY", 9},
  //   {"LOAD", 10},
  //   {"STORE", 11},
  //   {"INPUT", 12},
  //   {"OUTPUT", 13},
  //   {"STOP", 14},
  // };

  operationSizeTable = {
    {"add", 2},
    {"sub", 2},
    {"mul", 2},
    {"div", 2},
    {"jmp", 2},
    {"jmpn", 2},
    {"jmpp", 2},
    {"jmpz", 2},
    {"copy", 3},
    {"load", 2},
    {"store", 2},
    {"input", 2},
    {"output", 2},
    {"stop", 1},
  };
  // operationSizeTable = {
  //   {"ADD", 2},
  //   {"SUB", 2},
  //   {"MUL", 2},
  //   {"DIV", 2},
  //   {"JMP", 2},
  //   {"JMPN", 2},
  //   {"JMPP", 2},
  //   {"JMPZ", 2},
  //   {"COPY", 3},
  //   {"LOAD", 2},
  //   {"STORE", 2},
  //   {"INPUT", 2},
  //   {"OUTPUT", 2},
  //   {"STOP", 1},
  // };

  // directiveTable["space"] = &Assembler::directiveSpace;
  directiveTable = {
    {"space", &Assembler::directiveSpace},
    {"const", &Assembler::directiveConst},
  };

} 


Assembler::~Assembler() { }


void Assembler::assemble(std::vector<std::string> sourceFileContent) {
  this->sourceFileContent = sourceFileContent; // tem cara de construtor

  runFirstPass();
  // sunSecondPass();

  std::cout << "\n\nsymbol table" << std::endl;
  std::cout << strToIntMapToString(symbolTable) << std::endl;
}


void Assembler::runFirstPass() {
  positionCounter = 0;
  lineCounter = 1;
  bool labelExists, foundLabel, operationFound, directiveFound;
  // std::vector<std::string> tokens;
  std::string label, operation, operand1, operand2;
  std::string savedLabelForLater;

  LineAndItsTokens lineAndItsTokens;

  for (std::string line : sourceFileContent) {
    // not necessarily length = 0
    // if line is empty: continue; lineCounter++;
    tokens = parseLine(line);
    if (tokens.empty())
      continue;

    lineAndItsTokens = { line, tokens };
    // std::cout << lineAndItsTokens << std::endl;

    // LABEL
    if (tokens.size() >= 2) {
      // if tokens.size() == 0: continue; savedLabelForLater=label; lineCounter++; // linha vazia
      // if label?.size() == 0: continue; savedLabelForLater=label; lineCounter++; // linha vazia
      // if (savedLabelForLater.length() > 0) {
      //   label = savedLabelForLater;
      //   savedLabelForLater = "";
      // }
      // else {
      //   label = tokens[0];
      // }
      labelExists = tokens[1] == ":";
      if (labelExists) {
        label = tokens[0]; // {"some_label", ":", ...}

        foundLabel = symbolTable.find(label) != symbolTable.end();
        if (!foundLabel) {
          symbolTable[label] = positionCounter;
          // std::cout << label << "<-" << std::to_string(positionCounter) << std::endl;
        }
        else {
          // adicionar erro: símbolo redefinido na linha {lineCounter}
        }
      }
    }

    // OPERATION
    if (tokens.size() >= 3 || (!labelExists && tokens.size() >= 2) || tokens.size() == 1) {
      if (tokens.size() >= 3)
        operation = tokens[2]; // {"some_label", ":", "ADD", ...}
      else 
        operation = tokens[0]; // {"input", "n2"}

      operationFound = opcodeTable.find(operation) != opcodeTable.end();
      if (operationFound) {
        // std::cout 
        //   << "positionCounter += " 
        //   << std::to_string(operationSizeTable[operation]) 
        //   << std::endl;
        positionCounter += operationSizeTable[operation];
      }
      else {
        directiveFound = directiveTable.find(operation) != directiveTable.end();
        if (directiveFound) {
          auto directiveFunctionPtr = directiveTable[operation];
          (this->*directiveFunctionPtr)();
        }
        else {
          //   Erro, operação não identificada
        }
      }
    }

    lineCounter++;
  }
} 


std::vector<std::string> Assembler::parseLine(std::string line) {
  int newStart = 0;
  int tokenStartsAt = 0;
  std::string token = "";
  std::vector<std::string> tokens;

  while (tokenStartsAt >= 0) {
    token = findNextTokenStartingFrom(newStart, line, tokenStartsAt);
    newStart = tokenStartsAt + token.length();
    tokens.push_back(token);
  }

  tokens.pop_back();
  tokens.shrink_to_fit();

  return tokens;
}


// std::string Assembler::findLabel(std::string line) {
//   char c;
//   bool labelFound = false;
//   int labelIndex = 0;
//   size_t i = 0;
//   std::string label = "";

//   for (i = 0; i < line.length(); i++) {
//     if (line[i] == ':' && !labelFound) {
//       labelFound = true;
//       labelIndex = i-1; // desconsiderar ':'

//       while (
//         labelIndex >= 0 && 
//         (line[labelIndex] != ' ' 
//         || line[labelIndex] != '\t' 
//         || line[labelIndex] == '_')
//       ) {
//         c = line[labelIndex--];
//         label.insert(0, 1, c);
//       }
      
//       validateLabel(label);

//       break;
//     }
//   }
  
//   return label;
// }


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
    isTokenDelimiter = c == ':' || c == ',';

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

// To pedindo pra criar bugs dificeis de serem resolvidos
void Assembler::directiveSpace() { 
  positionCounter++;
}


void Assembler::directiveConst() {
  positionCounter += 2;
}




/////////////////////////////////////
// Some helper functions and stuff //
/////////////////////////////////////
std::ostream &operator<<(std::ostream& os, const LineAndItsTokens& line) {
  std::string tokens = "";
  for(auto token : line.tokens)
    tokens.append("\"" + token + "\", ");
  return os << "\"" << line.line << "\"" << ", {" << tokens << "}";
}


std::string tokensToString(std::vector<std::string> tokens) {
  std::string finalString = "";

  for (auto &t : tokens) {
    finalString.append("\"" + t + "\" ");
  }
  
  return finalString;
}

std::string strToIntMapToString(std::map<std::string, int> map) {
  std::string finalString = "[\n";
  for (auto & pair : map) {
    finalString.append("  " + pair.first + ": " + std::to_string(pair.second) + "\n");
  }
  return finalString + "]";
}
