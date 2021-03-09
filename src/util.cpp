
#include "../include/util.h"

/////////////////////////////////////
// Some helper functions and stuff //
/////////////////////////////////////
std::ostream &operator<<(std::ostream& os, const LineAndItsTokens& line) {
  std::string tokens = "";
  for(auto token : line.tokens)
    tokens.append("\"" + token + "\", ");
  return os << "\"" << line.line << "\"" << ", {" << tokens << "}";
}


std::string tokensToString(std::vector<std::string> tokens) {
  std::string finalString = "";

  for (auto &t : tokens) {
    finalString.append("\"" + t + "\" ");
  }
  
  return finalString;
}

std::string strToIntMapToString(std::map<std::string, int> map) {
  std::string finalString = "[";
  for (auto & pair : map) {
    finalString.append(pair.first + ": " + std::to_string(pair.second) + ", ");
  }
  return finalString + "]";
}
