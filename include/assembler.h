#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include <iostream>
#include <vector>
#include <map>


class Assembler {
private:
  int positionCounter;

  int lineCounter;

  std::map<std::string, int> _symbolTable;
  
  std::map<std::string, int> _opcodeTable;
  
  // instructionSizeTable?
  std::map<std::string, int> _operationSizeTable;
  
  std::map<std::string, int (Assembler::*)(int positionCounter)> _directiveTable;

  std::vector<std::string> _sourceFileContent;
  
  std::vector<std::string> _tokens;


public:
  Assembler();

  ~Assembler();

  void assemble(std::vector<std::string> sourceFileContent);
  
  void runFirstPass();

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

  void validateLabel(std::string label);
  
  
  std::map<std::string, int> symbolTable();


  // Diretivas

  // Função da diretiva SPACE
  int directiveSpace(int posCounter);


  // Função da diretiva CONST
  int directiveConst(int posCounter);
};


/////////////////////////////////////
// Some helper functions and stuff //
/////////////////////////////////////

/**
 * @brief Classe para facilitar testes unitários. 
 * Linha (string) e tokens esperados (vetor de strings).
 * Registro para facilitar testes unitários.
*/
struct LineAndItsTokens {
  std::string line;
  std::vector<std::string> tokens;

  friend std::ostream &operator<<(std::ostream& os, const LineAndItsTokens& line);
};


std::string tokensToString(std::vector<std::string> tokens);


std::string strToIntMapToString(std::map<std::string, int> map);


#endif // ASSEMBLER_H_INCLUDED
