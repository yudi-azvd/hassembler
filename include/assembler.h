#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>


class Assembler {
private:
  int _textSectionSize;
  
  int _dataSectionSize;

  bool _isRunningSecondPass = false;
  
  bool _dataSectionComesFirst = true; // os exemplos do professor.

  std::string _filename;

  std::map<std::string, int> _symbolTable;
  
  std::map<std::string, int> _opcodeTable;
  
  // instructionSizeTable?
  std::map<std::string, int> _operationSizeTable;
  
  std::map<std::string, int (Assembler::*)(int positionCounter)> _directiveTable;

  std::vector<std::string> _sourceFileContent;
  
  std::vector<std::string> _tokens;
  
  std::vector<int> _objectCode;

  std::vector<std::string> _errors;

  void _initialize();

public:
  Assembler(std::string filename = "");
  
  ~Assembler();

  void assemble();
  
  void getInputFileContent(std::string filename);

  /**
   * Determina se secão de dados vem antes ou depois
   * o resultado é guardado em _dataSectionComesFirst.
   */
  void runZerothPass();

  void runFirstPass();

  void runSecondPass();

  // void adjustForDataSection(std::map<std::string, int>& symbolTable, int offset);
  void adjustForDataSection();

  void adjustObjectCode();

  std::string findLabel(int& labelPosition, int& colonPosition);

  std::string findOperation(int labelPosition, int& operationPosition);

  std::vector<std::string> findOperands(int operationPosition);
  
  void generateOutput();

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
  int directiveSpace(int posCounter);


  // Função da diretiva CONST
  int directiveConst(int posCounter);


  // Função da diretiva SECTION
  int directiveSection(int posCounter);
};


#endif // ASSEMBLER_H_INCLUDED
