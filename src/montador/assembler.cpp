#include <vector>
#include <algorithm>

#include "../../include/assembler.h"
#include "../../include/errors.h"
#include "../../include/util.h"


Assembler::Assembler(std::string filename) { 
  if (!filename.empty())
    _filename = filename;
  _initialize();
}


void Assembler::_initialize() {
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
    {"section", &Assembler::directiveSection},
    {"begin", &Assembler::directiveBegin},
  };
}


Assembler::~Assembler() { }


void Assembler::getInputFileContent(std::string fn) { 
  std::string line;
  _filename = fn;
  std::vector<std::string> sourceFileContent;
  std::fstream infile(_filename);

  if (!infile.is_open()) {
    _errors.push_back("Arquivo não encontrado: " + _filename);
  }

  std::map<std::string, int> symbolTable;

  while (std::getline(infile, line)) {
    sourceFileContent.push_back(line);
  }

  _fileContent = sourceFileContent;

  infile.close();
}


void Assembler::assemble() {
  getInputFileContent(_filename);
  runZerothPass();
  runFirstPass();

  if (_dataSectionComesFirst) {
    adjustForDataSection();
  }

  runSecondPass();

  if (_dataSectionComesFirst) {
    adjustObjectCode();
  }

  generateOutput();
}


void Assembler::runZerothPass() {
  int lineCounter = 1;
  int dataSectionAtLine = 0;
  int textSectionAtLine = 0;

  for (std::string line: _fileContent) {
    _tokens = parseLine(line);
    if (_tokens.empty()) {
      lineCounter++;
      continue;
    }

    if (toLower(_tokens[0]) != "section") {
      continue;
    }

    if (toLower(_tokens[1]) == "data") {
      dataSectionAtLine = lineCounter;
    }
    else if (toLower(_tokens[1]) == "text") {
      textSectionAtLine = lineCounter;
    }

    if (dataSectionAtLine > 0 && textSectionAtLine > 0) {
      break;
    }

    lineCounter++;
  }

  _dataSectionComesFirst = dataSectionAtLine < textSectionAtLine;
}


void Assembler::runZeroth2Pass() {
  int lineCounter = 1;
  bool lineHasExtern, lineHasPublic, lineHasBegin, lineHasEnd;
  std::vector<int> linesToBeCommetendOut;
  std::vector<std::string> loweredTokens;

  for (std::string line: _fileContent) {
    _tokens = parseLine(line);
    if (_tokens.empty()) {
      lineCounter++;
      continue;
    }
    
    loweredTokens = stringVectorLowerCased(_tokens);

    lineHasExtern = findInVector(loweredTokens, "extern");
    lineHasPublic = findInVector(loweredTokens, "public");
    lineHasBegin = findInVector(loweredTokens, "begin");
    lineHasEnd = findInVector(loweredTokens, "end");

    // assumindo que apenas uma delas é verdadeira em uma linha
    if (lineHasExtern) {
      // adicionar simbolo na tabela de uso
      // marcar linha para ser comentada fora
    }
    else if (lineHasPublic) {
      // adicionar simbolo na tabela de definições
      // marcar linha para ser comentada fora      
    }
    else if (lineHasBegin) {
      // salvar nome do módulo em algum lugar
      // marcar linha para ser comentada fora
    }
    else if (lineHasEnd) {
      // precisa fazer algo?
      // marcar linha para ser comentada fora
    }
    else {
      // faz nada
    }
  }
}


void Assembler::runFirstPass() {
  _textSectionSize = 0;
  _dataSectionSize = 0;
  int positionCounter = 0, lineCounter = 1;
  bool labelExists, labelWasFound, instructionWasFound, directiveWasFound;
  std::string label, operation, operand1, operand2;
  std::string savedLabelForLater;

  for (std::string line : _fileContent) {
    _tokens = parseLine(line);
    if (_tokens.empty()) {
      lineCounter++;
      continue;
    }

    // LABEL
    int labelPosition = -1;
    int colonPosition = -1;
    label = findLabel(labelPosition, colonPosition);
    labelExists = !label.empty();

    if (labelExists) {
      // Se as próximas linhas do código fonte não tiverem rótulo
      // a variável label não vai ser sobrescrita, ou seja, um label sozinho
      // numa linha fica guardado até a próxima linha com rótulo
      // label = _tokens[0]; // {"some_label", ":", ...}
      labelWasFound = _symbolsTable.find(toLower(label)) != _symbolsTable.end();
      if (!labelWasFound) {
        if (!isValidSymbol(label)) {
          _errors.push_back("Erro Léxico, linha " + std::to_string(lineCounter) 
            + ": símbolo '" + label + "' é inválido."
          );
        }
        else {
          _symbolsTable[toLower(label)] = positionCounter;
        }
      }
      else {
        _errors.push_back("Erro Semântico, linha " + std::to_string(lineCounter) 
          + ": símbolo '" + label + "' redefinido."
        );
      }
    }

    int operationPosition = -1;
    operation = findOperation(labelPosition, operationPosition);
    // é um chute pra determinar a operação
    if (!labelExists && savedLabelForLater.empty())
      operation = _tokens[0];

    std::vector<std::string> operands = findOperands(labelPosition, operationPosition);
    operand1 = operands.size() >= 1 ? operands[0] : "";

    bool labelIsAloneInLine = labelExists && operation.empty() && operands.size() == 0;
    if (labelIsAloneInLine) {
      continue;
    }

    std::string lowerCasedOperation = toLower(operation);
    instructionWasFound = _opcodeTable.find(lowerCasedOperation) != _opcodeTable.end();
    if (instructionWasFound) {
      int operationSize = _operationSizeTable[lowerCasedOperation];
      positionCounter += operationSize;
      _textSectionSize += operationSize;
    }
    else {
      directiveWasFound = _directiveTable.find(lowerCasedOperation) != _directiveTable.end();
      if (directiveWasFound) {
        auto directiveFunctionPtr = _directiveTable[lowerCasedOperation];
        positionCounter = (this->*directiveFunctionPtr)(positionCounter, operands);
        // assumindo que todas as diretivas alocam UM espaço de memória.
        if (lowerCasedOperation != "section") _dataSectionSize++;
      }
      else if (labelExists) { // || savedLabelForLater
        // Assumindo que diretivas sempre aparecem diretamente _associadas_ a 
        // um rótulo
        _errors.push_back("Erro Semântico, linha " + std::to_string(lineCounter) +
          ": diretiva '" + operation + "' não identificada."
        );
      }
      else {
        _errors.push_back("Erro Semântico, linha " + std::to_string(lineCounter) +
          ": instrução '" + operation + "' não identificada."
        );
      }
    }

    lineCounter++;
  }
} 


void Assembler::runSecondPass() {
  int positionCounter = 0, lineCounter = 1;
  bool labelExists, operationFound, directiveFound, 
    operand1Found, operand2Found;
  std::string label, operation, operand1, operand2;
  std::string savedLabelForLater;

  _isRunningSecondPass = true;

  for (std::string line : _fileContent) {
    _tokens = parseLine(line);
    if (_tokens.empty()) {
      lineCounter++;
      continue;
    }

    int labelPosition = -1;
    int colonPosition = -1;
    label = findLabel(labelPosition, colonPosition);
    labelExists = !label.empty();

    int operationPosition = -1;
    operation = findOperation(labelPosition, operationPosition);

    std::vector<std::string> operands = findOperands(labelPosition, operationPosition);
    operand1 = operands.size() >= 1 ? operands[0] : "";
    int numberOfOperands = operands.size();

    bool labelIsAloneInLine = labelExists && operation.empty() && operands.size() == 0;
    if (labelIsAloneInLine) {
      savedLabelForLater = label;
      continue;
    }

    if (toLower(operation) == "copy") { 
      // 0        1   2
      // "label1" "," "label2"
      operand2 = operands.size() >= 2 ? operands[2] : "";
      numberOfOperands--; // descontar a "," presente em operands.
    }

    std::string lowerCasedOperation = toLower(operation);
    directiveFound = _directiveTable.find(lowerCasedOperation) != _directiveTable.end();

    if (!directiveFound) { // GAMBIARRA, tenho que corrigir ainda
      // OPERAND 1
      if (std::isdigit(operand1[0])) {
        _errors.push_back("Erro Sintático, linha " + std::to_string(lineCounter) 
          + ": operando '" + operand1 + "' deve ser um rótulo."
        );
      }
      else {
        operand1Found = _symbolsTable.find(toLower(operand1)) != _symbolsTable.end();
        if (!operand1Found && operand1 != "") {
          _errors.push_back("Erro Semântico, linha " + std::to_string(lineCounter) 
            + ": operando '" + operand1 + "' indefinido."
          );
        }
      }

      // OPERAND 2
      if (toLower(operation) == "copy") {
        if (std::isdigit(operand2[0])) {
          _errors.push_back("Erro Sintático, linha " + std::to_string(lineCounter) 
            + ": operando '" + operand2 + "' deve ser um rótulo."
          );
        }
        else {
          operand2Found = _symbolsTable.find(toLower(operand2)) != _symbolsTable.end();
          if (!operand2Found) {
            _errors.push_back("Erro Semântico, linha " + std::to_string(lineCounter) 
              + ": operando '" + operand2 + "' indefinido."
            );
          }
        }
      }
    }

    // OPERATION
    operationFound = _opcodeTable.find(lowerCasedOperation) != _opcodeTable.end();
    if (operationFound) {
      int operationSize = _operationSizeTable[lowerCasedOperation];
      positionCounter += operationSize;
      
      // O número de operandos de uma operação é o tamanho da operação
      // menos 1 por causa do símbolo da própria operação, o que sobra 
      // é operando.
      if (numberOfOperands != (operationSize-1)) {
        _errors.push_back("Erro Sintático, linha " + std::to_string(lineCounter)
          + ": instrução '" + operation + "' com número de operandos errado."
        );
      }
      
      _objectCode.push_back(_opcodeTable[lowerCasedOperation]);
      
      if (lowerCasedOperation != "stop")
        _objectCode.push_back(_symbolsTable[toLower(operand1)]);
      if (lowerCasedOperation == "copy") 
        _objectCode.push_back(_symbolsTable[toLower(operand2)]);
      // Se não estiver correto, erro sintático

    }
    else { // DIRECTIVE
      if (directiveFound) {
        auto directiveFunctionPtr = _directiveTable[lowerCasedOperation];

        // SPACE NÃO PODE RECEBER OPERANDOS
        // Essa checagem deveria acontecer dentro da função da diretiva(?)
        bool constHasWrongNumberOfOperands = lowerCasedOperation == "const" && operands.size() != 1;
        bool spaceHasWrongNumberOfOperands = lowerCasedOperation == "space" && operands.size() != 0;
        std::string strOperand = operands.size() > 0 ? operands[0] : "";
        if (constHasWrongNumberOfOperands || spaceHasWrongNumberOfOperands) {
          _errors.push_back("Erro Sintático, linha " + std::to_string(lineCounter)
            + ": diretiva '" + operation + "' com número de operandos errado."
          );
        }
        else if (lowerCasedOperation == "const" && !isNumber(strOperand)) {
          _errors.push_back("Erro Sintático, linha " + std::to_string(lineCounter)
            + ": operando '" + strOperand + "' deve ser um inteiro."
          );
        }
        else {
          positionCounter = (this->*directiveFunctionPtr)(positionCounter, operands);
        }
      }
      else if (labelExists) {
        // assumindo que diretivas sempre aparecem _associadas_ a um rótulo
        _errors.push_back("Erro Semântico, linha " + std::to_string(lineCounter) +
          ": diretiva '" + operation + "' não identificada."
        );
      }
      // else {
      //   _errors.push_back("Erro Semântico, linha " + std::to_string(lineCounter) +
      //     ": instrução '" + operation + "' não identificada."
      //   );
      // }
    }

    lineCounter++;
  }
  _isRunningSecondPass = false;
}


void Assembler::adjustForDataSection() {
  std::map<std::string, int>::iterator it;

  for (auto const& pair : _symbolsTable) {
    auto key = pair.first;
    int positionCounter = _symbolsTable[key];
    bool isLabelInTextSection = positionCounter >= _dataSectionSize;

    if (isLabelInTextSection) {
      _symbolsTable[key] -= _dataSectionSize;
    }
    else {
      _symbolsTable[key] += _textSectionSize;
    }
  }
}


void Assembler::adjustObjectCode() {
  // Se tenho que ajustar o código objeto, SECTION DATA
  // ctz vem primeiro
  // dataSectionSize + _textSectionSize == _objectCode.size() => True
  int textSectionStart = _objectCode.size() - _textSectionSize;

  // começar por SECTION TEXT
  auto adjustedObjectCode = std::vector<int>(
    _objectCode.begin() + textSectionStart, _objectCode.end()
  );

  // acrescentar SECTION DATA no final
  adjustedObjectCode.insert(
    adjustedObjectCode.end(), 
    _objectCode.begin(), 
    _objectCode.end()-_textSectionSize
  );

  _objectCode = adjustedObjectCode;
}


std::string Assembler::findLabel(int& labelPosition, int& colonPosition) {
  std::string tk, label;
  // : ADD LABEL1  ;; ??? 
  for (size_t i = 0; i < _tokens.size(); i++) {
    // Considero como label, mesmo que esteja na posição errada.
    if (_tokens[i] == ":" && i >= 1) {
      colonPosition = i;
      labelPosition = i-1;
      label = _tokens[i-1];
    }
  }

  return label;
}


std::string Assembler::findOperation(int labelPosition, int& operationPosition) {
  //       : INSTRUCTION [OP1, [OP2]]
  // LABEL : INSTRUCTION [OP1, [OP2]]
  // LABEL : DIRECTIVE   [OP1]
  // LABEL : 
  // _tokens[labelPostion+0] => "label"
  // _tokens[labelPostion+1] => ":"
  // _tokens[labelPostion+2] => potencial operação
  auto labelExists = labelPosition >= 0;
  auto labelIsAloneInLine = _tokens.size() == 2; // {"label", ":"}

  if (labelExists && labelIsAloneInLine) {
    return "";
  }

  if (labelExists) {
    operationPosition = 2;
    return _tokens[2];
  }
  else {
    operationPosition = 0;
    return _tokens[0];
  }
}


std::vector<std::string> Assembler::findOperands(int labelPosition, int operationPosition) {
  std::vector<std::string> operands;

  auto labelExists = labelPosition >= 0;
  auto labelIsAloneInLine = _tokens.size() == 2; // {"label", ":"}

  if (labelExists && labelIsAloneInLine) {
    return operands;
  }

  size_t start = operationPosition >= 0 ? operationPosition+1 : 0;

  for (size_t i = start; i < _tokens.size(); i++) {
    operands.push_back(_tokens[i]);
  }

  return operands;
}


void Assembler::generateOutput() {
  if (_errors.size() > 0) {
    for (auto err : _errors) {
      std::cout << err << std::endl;
    }
    return;
  }

  std::string finalString = "", outFilename = "";

  // o nome do arquivo está entre '/' e '.'
  bool insertMode = false;
  for (int i = _filename.size() - 1; i >= 0; --i) {
    if (insertMode) {
      outFilename.insert(0, 1,  _filename[i]);
    }

    if (_filename[i] == '/') {
      break;
    }

    if (_filename[i] == '.') {
      insertMode = true;
      continue;
    }
  }

  if (outFilename[0] != '/') { // "nome" => "/nome"
    outFilename.insert(0, 1, '/');
  }

  outFilename.insert(0, "."); // "/nome" => "./nome"
  outFilename.append(".obj"); // "./nome.obj"

  std::fstream outputFile;
  outputFile.open(outFilename, std::ios::out);

  for (auto n : _objectCode) {
    finalString.append(std::to_string(n) + " ");
  }
  
  outputFile << finalString;
  outputFile.close();
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

  if (symbol.length() >= 50) {
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
  return _symbolsTable;
}


void Assembler::setSymbolTable(std::map<std::string, int> st) {
  _symbolsTable = st;
}


void Assembler::setSourceFileContent(std::vector<std::string> content) {
  _fileContent = content;
}


std::vector<std::string> Assembler::errors() { 
  return _errors;
}


std::vector<int> Assembler::objectCode() { 
  return _objectCode;
}


int Assembler::directiveSpace(int posCounter, std::vector<std::string> operands) { 
  if (_isRunningSecondPass) {
    _objectCode.push_back(0);
  }
  return posCounter + 1;
}


// vai dar errado se separar a label da linha?
int Assembler::directiveConst(int posCounter, std::vector<std::string> operands) {
  // Assumindo que todo caso correto
  // de diretiva const vem na forma a seguir:
  // {"DOIS", ":", "const", "2"}
  // E se vier assim em duas linhas?
  // {"DOIS", ":"}
  // { "const", "2"}

  if (!_isRunningSecondPass) {
    return posCounter+1;
  }
  
  std::string strOperand = operands.size() > 0 ? operands[0] : "";
  int operand = std::atoi(strOperand.c_str());
  _objectCode.push_back(operand);
  return posCounter + 1;
}


int Assembler::directiveBegin(int posCounter, std::vector<std::string> operands) {
  return posCounter;
}


int Assembler::directiveExtern(int posCounter, std::vector<std::string> operands) {
  return posCounter;
}


int Assembler::directiveSection(int posCounter, std::vector<std::string> operands) {
  return posCounter;
}
