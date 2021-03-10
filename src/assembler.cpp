#include <vector>

#include "../include/assembler.h"
#include "../include/errors.h"
#include "../include/util.h"


Assembler::Assembler(std::vector<std::string> sourceFileContent) { 
  _sourceFileContent = sourceFileContent;

  _opcodeTable = {
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

  _operationSizeTable = {
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

  // directiveTable["space"] = &Assembler::directiveSpace;
  _directiveTable = {
    {"space", &Assembler::directiveSpace},
    {"const", &Assembler::directiveConst},
  };
} 


Assembler::~Assembler() { }


void Assembler::assemble(std::vector<std::string> sourceFileContent) {
  this->_sourceFileContent = sourceFileContent; // tem cara de construtor

  runFirstPass();
  // sunSecondPass();

  // std::cout << "\n\nsymbol table" << std::endl;
  // std::cout << strToIntMapToString(_symbolTable) << std::endl;
}


void Assembler::runFirstPass() {
  _positionCounter = 0;
  _lineCounter = 1;
  bool labelExists, foundLabel, operationFound, directiveFound;
  std::string label, operation, operand1, operand2;
  std::string savedLabelForLater;

  // LineAndItsTokens lineAndItsTokens;

  for (std::string line : _sourceFileContent) {
    // not necessarily length = 0
    // if line is empty: continue; lineCounter++;
    _tokens = parseLine(line);
    if (_tokens.empty()) {
      _lineCounter++;
      continue;
    }

    // lineAndItsTokens = { line, _tokens };
    // std::cout << lineAndItsTokens << std::endl;

    // LABEL
    if (_tokens.size() >= 2) {
      // if tokens.size() == 0: continue; savedLabelForLater=label; lineCounter++; // linha vazia
      // if label?.size() == 0: continue; savedLabelForLater=label; lineCounter++; // linha vazia
      // if (savedLabelForLater.length() > 0) {
      //   label = savedLabelForLater;
      //   savedLabelForLater = "";
      // }
      // else {
      //   label = tokens[0];
      // }
      labelExists = _tokens[1] == ":";
      if (labelExists) {
        label = _tokens[0]; // {"some_label", ":", ...}

        foundLabel = _symbolTable.find(label) != _symbolTable.end();
        if (!foundLabel) {
          if (!isValidSymbol(label)) {
            _errors.push_back("Erro Léxico, linha " + std::to_string(_lineCounter) +
              ": símbolo '" + label + "' é inválido."
            );
          }
          else {
            _symbolTable[label] = _positionCounter;
          }
        }
        else {
          // adicionar erro: símbolo redefinido na linha {lineCounter}
          _errors.push_back("Erro Semântico, linha " + std::to_string(_lineCounter) +
            ": símbolo '" + label + "' redefinido."
          );
        }
      }
    }

    // OPERATION
    if (_tokens.size() >= 3 || (!labelExists && _tokens.size() >= 2) || _tokens.size() == 1) {
      if (_tokens.size() == 4 && labelExists)
        operation = _tokens[2]; // {"some_label", ":","copy", "zero", "," "older"}
      else if (_tokens.size() == 4)
        operation = _tokens[0]; // {"copy", "zero", "," "older"}
      else if (_tokens.size() == 3)
        operation = _tokens[2]; // {"some_label", ":", "ADD", ...}
      else 
        operation = _tokens[0]; // {"input", "n2"}

      operationFound = _opcodeTable.find(operation) != _opcodeTable.end();
      if (operationFound) {
        _positionCounter += _operationSizeTable[operation];
      }
      else {
        directiveFound = _directiveTable.find(operation) != _directiveTable.end();
        if (directiveFound) {
          auto directiveFunctionPtr = _directiveTable[operation];
          _positionCounter = (this->*directiveFunctionPtr)(_positionCounter);
        }
        else if (labelExists) { // savedLabelForLaterExists?
          // assumindo que diretivas sempre aparecem _associadas_ a um rótulo
          _errors.push_back("Erro Semântico, linha " + std::to_string(_lineCounter) +
            ": diretiva '" + operation + "' não identificada."
          );
        }
        else {
          _errors.push_back("Erro Semântico, linha " + std::to_string(_lineCounter) +
            ": instrução '" + operation + "' não identificada."
          );
        }
      }
    }

    _lineCounter++;
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


bool Assembler::isValidSymbol(std::string symbol) {
  if (!std::isalpha(symbol[0]) && symbol[0] != '_') {
    return false;
  }

  bool isValidChar = true;
  for (auto c : symbol) {
    isValidChar = std::isalpha(c) || std::isdigit(c) || c == '_';
    if (!isValidChar) {
      return false;
    }
  }

  return true;
}


std::map<std::string, int> Assembler::symbolTable() { 
  return _symbolTable;
}


std::vector<std::string> Assembler::errors() { 
  return _errors;
}


int Assembler::directiveSpace(int posCounter) { 
  return posCounter + 1;
}


int Assembler::directiveConst(int posCounter) {
  return posCounter + 1;
}
