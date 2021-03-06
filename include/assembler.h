#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include <iostream>
#include <vector>
#include <map>

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


class Assembler {
private:

  std::map<std::string, int> symbolTable;
  
  std::map<std::string, int> opcodeTable;

  std::vector<std::string> sourceFileContent;


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
};

#endif // ASSEMBLER_H_INCLUDED
