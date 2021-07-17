#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <iostream>
#include <vector>

/**
 * Realiza a análise léxica da linha.
 * Deveria Zerar o estado do objeto a cada vez que parseTokens/runs é chamado.
 */
class Scanner {
public:
  // Scanner();

  ~Scanner();

  std::vector<std::string> parseTokens(const std::string line);

  std::string findNextTokenStartingFrom(
    size_t start,
    std::string line,
    int& tokenStartsAt
  );

  bool isValidSymbol(std::string symbol);
};


#endif // SCANNER_H_INCLUDED

/*
*/
