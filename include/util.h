#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

/////////////////////////////////////
// Some helper functions and stuff //
/////////////////////////////////////

#include <algorithm>
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


std::string vectorToString(std::vector<std::string> tokens);


std::string vectorToString(std::vector<int> v);


std::string strToIntMapToString(std::map<std::string, int> map);


bool findErrorWith(std::string str, std::vector<std::string>& errors);


std::string toLower(std::string str);
  

#endif // !UTIL_H_INCLUDED