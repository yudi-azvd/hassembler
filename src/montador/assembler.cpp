#include <vector>
#include <algorithm>
#include <sstream>

#include "assembler.h"
#include "errors.h"
#include "util.h"

Assembler::Assembler(std::vector<std::string> filenames) { 
  if (!filenames.empty())
    _filenames = filenames;
  _initialize();
  _fileContent = {};
}


Assembler::Assembler(std::string filename) { 
  if (!filename.empty())
    _filename = filename;
  _initialize();
  _fileContent = {};
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


void Assembler::getMultipleFileContents() {
  for (auto filename : _filenames) {
    getFileContent(filename);
  }
}


void Assembler::getFileContent(std::string filename) { 
  std::string line;
  _filename = filename;
  std::vector<std::string> fileContent;
  std::fstream infile(filename);

  if (!infile.is_open()) {
    _errors.push_back("Arquivo não encontrado: " + filename);
  }

  while (std::getline(infile, line)) {
    fileContent.push_back(line);
  }

  infile.close();

  _filesContents.push_back(fileContent);
}


void Assembler::assemble() {
  getMultipleFileContents();

  size_t fileContentCounter = 0;
  for (; fileContentCounter < _filesContents.size(); fileContentCounter++) {
    _fileContent = _filesContents[fileContentCounter];

    runZerothPass();
    runZerothPass2(fileContentCounter);
    runFirstPass(_filesContents[fileContentCounter]);

    if (_dataSectionComesFirst) {
      adjustInternalSymbolsTable();
      // adjustExternalSymbolsTable();
      adjustDefinitionsTable(); // faz diferença???
    }

    runSecondPass(_filesContents[fileContentCounter]);

    if (_dataSectionComesFirst) {
      adjustUsageTable();
      adjustRelocationBitMap();
      adjustObjectCode();
    }

    _modulenames.push_back(_modulename);
    _modulename.clear();

    _symbolsTables.push_back(_symbolsTable);
    _symbolsTable.clear();

    _definitionsTables.push_back(_definitionsTable);
    _definitionsTable.clear();

    _usageTables.push_back(_usageTable);
    _usageTable.clear();
    _externalSymbolsTables.push_back(_externalSymbolsTable);
    _externalSymbolsTable.clear();

    _relocations.push_back(_relocationBitMap);
    _relocationBitMap.clear();

    _objectCodes.push_back(_objectCode);
    _objectCode.clear();
  } 

  checkIfAllFilesHaveModules();
  generateMultipleOutputs();
  // outputData();
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
      lineCounter++;
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


void Assembler::runZerothPass2(int fileContentCounter) {
  int lineCounter = 1;
  bool lineHasExtern, lineHasPublic, lineHasBegin, lineHasEnd;
  std::string label;
  std::vector<std::string> lowerCasedTokens;

  for (std::string line: _fileContent) {
    _tokens = parseLine(line);
    if (_tokens.empty()) {
      lineCounter++;
      continue;
    }
    
    lowerCasedTokens = stringVectorLowerCased(_tokens);

    lineHasExtern = findInVector(lowerCasedTokens, "extern");
    lineHasPublic = findInVector(lowerCasedTokens, "public");
    lineHasBegin = findInVector(lowerCasedTokens, "begin");
    lineHasEnd = findInVector(lowerCasedTokens, "end");

    // assumindo que apenas uma delas é verdadeira em uma linha
    if (lineHasExtern) {
      label = _tokens[0]; // {"label", ":", "extern"}
      _externalSymbolsTable[toLower(label)] = 0;
      _filesContents[fileContentCounter][lineCounter-1].insert(0, 1, ';');
    }
    else if (lineHasPublic) {
      label = _tokens[1]; // {"public", "label"}
      _definitionsTable[toLower(label)] = -1;
      _filesContents[fileContentCounter][lineCounter-1].insert(0, 1, ';');
    }
    else if (lineHasBegin) {
      _modulename = _tokens[0];
      bool singleFileWithModule = (_filenames.size() == 1) && lineHasBegin;
      if (singleFileWithModule)
        _errors.push_back("Não é permitido o uso de BEGIN e END com arquivo único.");
    }
    else if (lineHasEnd) {
      // checar se pode ter begin/end; lançar exceção
      // precisa fazer algo?
      _filesContents[fileContentCounter][lineCounter-1].insert(0, 1, ';');
    }
    else {
      // faz nada
    }

    lineCounter++;
  }
}


void Assembler::checkIfAllFilesHaveModules() {
  bool allFilesHaveModules = _modulenames.size() != _filenames.size();
  if (!allFilesHaveModules && _filenames.size() > 1) {
    _errors.push_back("Para montar mais de um arquivo, é necessário que cada um"
      " deles tenham um módulo");
  }
}


void Assembler::runFirstPass(std::vector<std::string>& fileContent) {
  _textSectionSize = 0;
  _dataSectionSize = 0;
  int positionCounter = 0, lineCounter = 1;
  bool labelExists, labelWasFound, instructionWasFound, directiveWasFound;
  std::string label, operation, operand1, operand2;
  std::string savedLabelForLater;

  for (std::string line : fileContent) {
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
          bool labelFoundInUsageTable = _externalSymbolsTable.find(toLower(label)) != _externalSymbolsTable.end();
          if (!labelFoundInUsageTable)
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
        if (lowerCasedOperation != "section" && lowerCasedOperation != "begin") 
          _dataSectionSize++;
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


void Assembler::runSecondPass(std::vector<std::string>& fileContent) {
  int positionCounter = 0, lineCounter = 1;
  bool labelExists, operationFound, directiveFound, 
    operand1FoundInInternSymTable, operand2FoundInInternSymTab,
    operand1FoundInExternSymTab, operand2FoundInExternSymTab;
  std::string label, operation, operand1, operand2;
  std::string savedLabelForLater;

  _isRunningSecondPass = true;

  for (std::string line : fileContent) {
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
        operand1FoundInInternSymTable = _symbolsTable.find(toLower(operand1)) != _symbolsTable.end();
        operand1FoundInExternSymTab = _externalSymbolsTable.find(toLower(operand1)) != _externalSymbolsTable.end();
        bool operand1NotFound = !operand1FoundInExternSymTab && !operand1FoundInInternSymTable;
        // aqui que adiciona o operand1
        if (operand1NotFound && !operand1.empty()) {
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
          operand2FoundInInternSymTab = _symbolsTable.find(toLower(operand2)) != _symbolsTable.end();
          operand2FoundInExternSymTab = _externalSymbolsTable.find(toLower(operand1)) != _externalSymbolsTable.end();
          bool operand2NotFound = !operand2FoundInExternSymTab && !operand2FoundInInternSymTab;

          // aqui que adiciona o operand1
          if (operand2NotFound && !operand2.empty()) {
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
      _relocationBitMap.push_back(0);
      
      if (lowerCasedOperation != "stop") {
        int discount = lowerCasedOperation == "copy" ? 2 : 1;
        int position = positionCounter-discount;
        if (operand1FoundInExternSymTab) {
          _objectCode.push_back(0);
          _externalSymbolsTable[toLower(operand1)] = 0;
          _usageTable.push_back(std::make_pair(toLower(operand1), position));
          _relocationBitMap.push_back(0);
        }
        else if (operand1FoundInInternSymTable) {
          _objectCode.push_back(_symbolsTable[toLower(operand1)]);
          _relocationBitMap.push_back(1);
        }
      }
      if (lowerCasedOperation == "copy") {
        int position = positionCounter-1;
        if (operand2FoundInExternSymTab) {
          _objectCode.push_back(0);
          _externalSymbolsTable[toLower(operand2)] = 0;
          _usageTable.push_back(std::make_pair(toLower(operand2), position));
          _relocationBitMap.push_back(0);
        }
        else if (operand2FoundInInternSymTab) {
          _objectCode.push_back(_symbolsTable[toLower(operand2)]);
          _relocationBitMap.push_back(1);
        }
      }
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
    }

    lineCounter++;
  }
  _isRunningSecondPass = false;
}


void Assembler::adjustInternalSymbolsTable() {
  for (auto const& pair : _symbolsTable) {
    auto key = pair.first;
    bool isLabelModulename = key == toLower(_modulename);
    if (isLabelModulename) {
      continue;
    }

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


void Assembler::adjustDefinitionsTable() {
  for (auto& pair : _definitionsTable) {
    auto key = pair.first;
    bool isLabelModulename = key == toLower(_modulename);
    if (isLabelModulename) {
      continue;
    }

    int positionCounter = _definitionsTable[key];
    bool isLabelInTextSection = positionCounter >= _dataSectionSize;
    if (isLabelInTextSection) {
      _definitionsTable[key] -= _dataSectionSize;
    }
    else {
      _definitionsTable[key] += _textSectionSize;
    }
  }
}


void Assembler::adjustUsageTable() {
  for (auto& pair : _usageTable) {
    pair.second -= _dataSectionSize;
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


void Assembler::adjustRelocationBitMap() {
  int textSectionStart = _objectCode.size() - _textSectionSize;

  // começar por SECTION TEXT
  auto adjustedRelocationBitMap = std::vector<int>(
    _relocationBitMap.begin() + textSectionStart, _relocationBitMap.end()
  );

  // acrescentar SECTION DATA no final
  adjustedRelocationBitMap.insert(
    adjustedRelocationBitMap.end(), 
    _relocationBitMap.begin(), 
    _relocationBitMap.end()-_textSectionSize
  );

  _relocationBitMap = adjustedRelocationBitMap;

}


void Assembler::extractDefinitionsTableFromSymbolsTable() {
  for (auto const& pair : _definitionsTable) {
    auto keyFromDefsTable = pair.first;
    // bool foundInST = _symbolsTable.find(keyFromDefsTable) != _symbolsTable.end();
    // if (!foundInST) {
    //   std::cout << "!!! não encontrado em TS: " << keyFromDefsTable << std::endl;
    // }
    _definitionsTable[keyFromDefsTable] = _symbolsTable[keyFromDefsTable];
  }
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


void Assembler::generateMultipleOutputs() {
  if (_errors.size() > 0) {
    for (auto err : _errors) {
      std::cout << err << std::endl;
    }
    return;
  }

  int counter = 0;
  for (auto filename : _filenames) {
    generateOutput(counter, filename);
    counter++;
  }
}


void Assembler::generateOutput(int counter, std::string filename) {
  std::string finalString = "", outFilename = "";
  std::stringstream ss;

  // o nome do arquivo está entre '/' e '.'
  bool insertMode = false;
  for (int i = filename.size() - 1; i >= 0; --i) {
    if (insertMode) {
      outFilename.insert(0, 1,  filename[i]);
    }

    if (filename[i] == '/') {
      break;
    }

    if (filename[i] == '.') {
      insertMode = true;
      continue;
    }
  }

  std::string pureOutFilename;
  if (outFilename[0] != '/') { 
    pureOutFilename = outFilename; // apenas "nome"
    outFilename.insert(0, 1, '/'); // "nome" => "/nome"
  }
  else {
    pureOutFilename = outFilename.substr(1, outFilename.length()-1);
  }

  outFilename.insert(0, "."); // "/nome" => "./nome"
  outFilename.append(".obj"); // "./nome.obj"

  std::fstream outputFile;
  outputFile.open(outFilename, std::ios::out);

  _objectCode = _objectCodes[counter];
  ss << "H " << pureOutFilename << std::endl;
  ss << "H " << _objectCode.size() << std::endl;

  _relocationBitMap = _relocations[counter];
  ss << "R ";
  for (auto bit : _relocationBitMap) {
    ss << bit;
  }

  ss << std::endl;
  _usageTable = _usageTables[counter];
  for (auto pair : _usageTable) {
    ss << "U " << pair.first << " " << pair.second << std::endl;
  }

  _definitionsTable = _definitionsTables[counter];
  for (auto pair : _definitionsTable) {
    ss << "D " << pair.first << " " << pair.second << std::endl;
  }

  ss << "T ";
  for (auto n : _objectCode) {
    ss << n << " ";
  }
  
  outputFile << ss.str();
  outputFile.close();
}


void Assembler::outputData() {
  for (size_t i = 0; i < _filenames.size(); i++) {
    std::cout << "\n### " << _filenames[i] << " ####"<< std::endl;

    std::cout << "\n>> USAGE table\n[";
    for (auto pair : _usageTables[i]) {
      std::cout << pair.first << " : " << pair.second << ", ";
    }
    std::cout << "]"<< std::endl;

    std::cout << "\n>> SYMBOLS table" << std::endl;
    std::cout << strToIntMapToString(_symbolsTables[i]) << std::endl;

    std::cout << "\n>> EXT SYMBOLS table" << std::endl;
    std::cout << strToIntMapToString(_externalSymbolsTables[i]) << std::endl;

    std::cout << "\n>> DEFINITIONS table" << std::endl;
    std::cout << strToIntMapToString(_definitionsTables[i]) << std::endl;

    std::cout << "\n>> OBJECT code: " << _objectCodes[i].size() << std::endl << "[";
    for (size_t i = 0; i < _objectCodes[i].size(); i++) 
      printf("%2d, ", (int) i);
    std::cout << "]" << std::endl << vectorToString(_objectCodes[i]) << std::endl;

    std::cout << "\n>> RELOCATION: " << _relocations[i].size() << std::endl;
    std::cout << vectorToString(_relocations[i]) << std::endl;
  }

  if (_errors.size() > 1) {
    std::cout << "\n>> ERRORS:" << std::endl;
    std::cout << vectorToString(_errors) << std::endl;
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
    _relocationBitMap.push_back(0);
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
  _relocationBitMap.push_back(0);

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
