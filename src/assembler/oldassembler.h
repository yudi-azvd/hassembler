#ifndef OLDASSEMBLER_H_INCLUDED
#define OLDASSEMBLER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "hasm/hasmdata.h"
#include "input/input.h"


class OldAssembler {
public:
  OldAssembler(HasmData* hasmData);

  OldAssembler(std::vector<std::string> filename);

  OldAssembler(std::string filename = "");

  ~OldAssembler();

  void assemble();

  void getMultipleFileContents();

  void getFileContent(std::string filename);

  /**
   * Determina se seção de dados vem antes ou depois
   * o resultado é guardado em _dataSectionComesFirst.
   */
  void runZerothPass();

  void runZerothPass2(int lineContentCounter);

  void checkIfAllFilesHaveModules();

  void runFirstPass(std::vector<std::string>& fileContent);

  void runSecondPass(std::vector<std::string>& fileContent);

  void adjustInternalSymbolsTable();

  void adjustDefinitionsTable();

  void adjustUsageTable();

  void adjustObjectCode();

  void adjustRelocationBitMap();

  void extractDefinitionsTableFromSymbolsTable();

  std::string findLabel(int& labelPosition, int& colonPosition);

  /**
   * Tenta (quase um chute educado) encontrar uma operação (instrução ou
   * diretiva) segundo a sintaxe do assembly hipotético.
   */
  std::string findOperation(int labelPosition, int& operationPosition);

  std::vector<std::string> findOperands(int labelPosition, int operationPosition);

  void generateOutput();

  void generateOutputForLinker(int counter, std::string filename);

  // Não é usado atualmente.
  void generateSimpleOutput(std::string filename);

  void outputErrors();

  void outputData();

  std::vector<std::string> parseLine(std::string line);

  /**
   * @brief Encontra um token na linha separado por espaços em branco.
   *
   * @param start Índice onde vai começar a procura.
   * @param line Linha a ser analisada.
   * @param tokenStartsAt Posição inicial do token encontrado.
   *
   * @return Token e sua posição inicial.
   */
  std::string findNextTokenStartingFrom(
    size_t start,
    std::string line,
    int& tokenStartsAt
  );

  bool isValidSymbol(std::string symbol);

  std::map<std::string, int> symbolTable();

  void setSymbolTable(std::map<std::string, int> st);

  void setSourceFileContent(std::vector<std::string> content);

  std::vector<std::string> errors();

  std::vector<int> objectCode();


  // Diretivas

  // Função da diretiva SPACE
  int directiveSpace(int posCounter, std::vector<std::string> operands);


  // Função da diretiva CONST
  int directiveConst(int posCounter, std::vector<std::string> operands);


  // Função da diretiva BEGIN
  int directiveBegin(int posCounter, std::vector<std::string> operands);


  int directiveExtern(int posCounter, std::vector<std::string> operands);


  // Função da diretiva SECTION
  int directiveSection(int posCounter, std::vector<std::string> operands);

private:
  HasmData* hasmData;

  int _textSectionSize;

  int _dataSectionSize;

  bool _isRunningSecondPass = false;

  bool _dataSectionComesFirst = true; // os exemplos do professor.

  std::map<std::string, int> _opcodeTable;

  // instructionSizeTable?
  std::map<std::string, int> _operationSizeTable;

  std::map<std::string, int (OldAssembler::*)(int positionCounter, std::vector<std::string> operands)> _directiveTable;

  std::vector<std::string> _modulenames;
  std::string _modulename;

  std::vector<std::string> _filenames;
  std::string _filename;

  std::vector<std::vector<std::string>> _filesContents;
  std::vector<std::string> _fileContent;

  std::vector<std::string> _tokens;

  std::vector<std::map<std::string, int>> _symbolsTables;
  std::map<std::string, int> _symbolsTable;

  std::vector<std::map<std::string, int>> _definitionsTables;
  std::map<std::string, int> _definitionsTable;

  std::vector<std::map<std::string, int>> _externalSymbolsTables;
  std::map<std::string, int> _externalSymbolsTable;

  std::vector<std::vector<std::pair< std::string, int>>> _usageTables;
  std::vector<std::pair< std::string, int>> _usageTable;

  std::vector<std::vector<int>> _objectCodes;
  std::vector<int> _objectCode;

  std::vector<std::vector<int>> _relocations;
  std::vector<int> _relocationBitMap;

  std::vector<std::string> _errors;

  void _initialize();
};


#endif // OLDASSEMBLER_H_INCLUDED
