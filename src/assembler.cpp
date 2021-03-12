#include <vector>

#include "../include/assembler.h"
#include "../include/errors.h"
#include "../include/util.h"


Assembler::Assembler(std::vector<std::string> sourceFileContent) { 
  _sourceFileContent = sourceFileContent;
  _isRunningSecondPass = false;
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

  for (std::string line : _sourceFileContent) {
    _tokens = parseLine(line);
    if (_tokens.empty()) {
      _lineCounter++;
      continue;
    }

    // LABEL
    if (_tokens.size() >= 2) {
      labelExists = _tokens[1] == ":";
      if (labelExists) {
        // Se as próximas linhas do código fonte não tiverem rótulo
        // a variável label não vai ser sobrescrita, ou seja, um label sozinho
        // numa linha fica guardado até a próxima linha com rótulo
        label = _tokens[0]; // {"some_label", ":", ...}

        foundLabel = _symbolTable.find(toLower(label)) != _symbolTable.end();
        if (!foundLabel) {
          if (!isValidSymbol(label)) {
            _errors.push_back("Erro Léxico, linha " + std::to_string(_lineCounter) +
              ": símbolo '" + label + "' é inválido."
            );
          }
          else {
            _symbolTable[toLower(label)] = _positionCounter;
          }
        }
        else {
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

      std::string lowerCasedOperation = toLower(operation);

      operationFound = _opcodeTable.find(lowerCasedOperation) != _opcodeTable.end();
      if (operationFound) {
        _positionCounter += _operationSizeTable[lowerCasedOperation];
      }
      else {
        directiveFound = _directiveTable.find(lowerCasedOperation) != _directiveTable.end();
        if (directiveFound) {
          auto directiveFunctionPtr = _directiveTable[lowerCasedOperation];
          _positionCounter = (this->*directiveFunctionPtr)(_positionCounter);
        }
        else if (labelExists) {
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


void Assembler::runSecondPass() {
  int positionCounter = 0, lineCounter = 1;
  bool labelExists, operationFound, directiveFound, 
    operand1Found, operand2Found;
  std::string label, operation, operand1, operand2;
  std::string savedLabelForLater;

  _isRunningSecondPass = true;

  for (std::string line : _sourceFileContent) {
    _tokens = parseLine(line);
    if (_tokens.empty()) {
      _lineCounter++;
      continue;
    }

    // LABEL
    if (_tokens.size() >= 2) {
      // é a única condição para label exitir?
      labelExists = _tokens[1] == ":";
    }

    // OPERATION and OPERANDS
    if (_tokens.size() >= 3 || (!labelExists && _tokens.size() >= 2) || _tokens.size() == 1) {
      if (_tokens.size() == 6 && _tokens[2] == "copy") {
        operation = _tokens[2]; // {"some_label", ":","copy", "zero", "," "older"}
        operand1 = _tokens[3]; 
        operand2 = _tokens[5]; 
      }
      else if (_tokens.size() == 4) {
        if (labelExists) { // {"some_label", ":", "ADD", "UM"}
                           // {"DOIS", ":", "const", "2"}
          operation = _tokens[2]; 
          operand1 = _tokens[3]; 
        }
        else { // {"copy", "zero", ",", "older"}
          operation = _tokens[0];
          operand1 = _tokens[1]; 
          operand2 = _tokens[3]; 
        }
      }
      else if(_tokens.size() == 3) {
        operation = _tokens[2]; // {"b:", ":", "space"}
      }
      else if (_tokens.size() == 2) { // {"input", "n2"}
        operation = _tokens[0]; 
        operand1 = _tokens[1]; 
      }
      else {
        operation = _tokens[0]; // {"stop"}
      }

      // OPERAND 1
      operand1Found = _symbolTable.find(toLower(operand1)) != _symbolTable.end();
      if (!operand1Found) {
        _errors.push_back("Erro Semântico, linha " + std::to_string(_lineCounter) +
          ": operando '" + operation + "' indefinido."
        );
      }

      // OPERAND 2
      if (toLower(operation) == "copy") {
        operand2Found = _symbolTable.find(toLower(operand2)) != _symbolTable.end();
        if (!operand2Found) {
          _errors.push_back("Erro Semântico, linha " + std::to_string(_lineCounter) +
            ": operando '" + operation + "' indefinido."
          );
        }
      }

      // OPERATION
      std::string lowerCasedOperation = toLower(operation);
      operationFound = _opcodeTable.find(lowerCasedOperation) != _opcodeTable.end();
      if (operationFound) {
        positionCounter += _operationSizeTable[lowerCasedOperation];
        
        // Se número e tipo dos operandos está correto
        _objectCode.push_back(_opcodeTable[lowerCasedOperation]);
        
        if (lowerCasedOperation != "stop")
          _objectCode.push_back(_symbolTable[toLower(operand1)]);
        if (lowerCasedOperation == "copy") 
          _objectCode.push_back(_symbolTable[toLower(operand2)]);
        // Se não estiver correto, erro sintático

      }
      else { // DIRECTIVE
        directiveFound = _directiveTable.find(lowerCasedOperation) != _directiveTable.end();
        if (directiveFound) {
          auto directiveFunctionPtr = _directiveTable[lowerCasedOperation];
          _positionCounter = (this->*directiveFunctionPtr)(_positionCounter);
        }
        else if (labelExists) {
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

    lineCounter++;
  }
  _isRunningSecondPass = false;
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


void Assembler::setSymbolTable(std::map<std::string, int> st) {
  _symbolTable = st;
}


std::vector<std::string> Assembler::errors() { 
  return _errors;
}


std::vector<int> Assembler::objectCode() { 
  return _objectCode;
}


int Assembler::directiveSpace(int posCounter) { 
  if (_isRunningSecondPass) {
    _objectCode.push_back(0);
  }
  return posCounter + 1;
}


// vai dar errado se separar a label da linha?
int Assembler::directiveConst(int posCounter) {
  // Assuminndo que todo caso de diretiva const vem
  // na forma a seguir:
  // {"DOIS", ":", "const", "2"}
  if (_isRunningSecondPass) {
    std::string strOperand = _tokens[3];
    int operand = std::atoi(strOperand.c_str());
    _objectCode.push_back(operand);
  }
  return posCounter + 1;
}
