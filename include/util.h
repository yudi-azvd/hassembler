#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

/////////////////////////////////////
// Some helper functions and stuff //
/////////////////////////////////////

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


std::string tokensToString(std::vector<std::string> tokens);


std::string strToIntMapToString(std::map<std::string, int> map);


#endif // !UTIL_H_INCLUDED