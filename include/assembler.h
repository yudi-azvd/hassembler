#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>


class Assembler {
private:
  bool _isRunningSecondPass = false;

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

public:
  Assembler(std::vector<std::string> sourceFileContent = {});

  ~Assembler();

  void assemble(std::vector<std::string> sourceFileContent = {});
  
  void getInputFileContent(std::string filename);

  void runFirstPass();

  void runSecondPass();
  
  void generateOutput();

  std::vector<std::string> parseLine(std::string line);

  // std::string findLabel(std::string line);
  
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
  
  std::vector<std::string> errors();
  
  std::vector<int> objectCode();


  // Diretivas

  // Função da diretiva SPACE
  int directiveSpace(int posCounter);


  // Função da diretiva CONST
  int directiveConst(int posCounter);
};


#endif // ASSEMBLER_H_INCLUDED
