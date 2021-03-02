#ifndef PARSELINE_H_INCLUDED
#define PARSELINE_H_INCLUDED

#include <iostream>
#include <vector>

struct LineAndItsTokens {
  std::string line;
  std::vector<std::string> tokens;

  friend std::ostream &operator<<(std::ostream& os, const LineAndItsTokens& line);
};


struct TokenizedLine {
  std::string label;
  std::string operation;
  std::string operand1;
  std::string operand2;
};


/**
 * @brief Processa uma linha retornando LABEL, OPERAÇÃO, OPERANDO_1 e OPERANDO_2
 * 
 * @param[in] line Linha
 */
std::vector<std::string> parseLine(std::string line);

std::string findLabel(std::string line);

#endif // !PARSELINE_H_INCLUDED