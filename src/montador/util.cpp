
#include "../../include/util.h"

/////////////////////////////////////
// Some helper functions and stuff //
/////////////////////////////////////
std::ostream &operator<<(std::ostream& os, const LineAndItsTokens& line) {
  std::string tokens = "";
  for(auto token : line.tokens)
    tokens.append("\"" + token + "\", ");
  return os << "\"" << line.line << "\"" << ", {" << tokens << "}";
}


std::string vectorToString(std::vector<std::string> tokens) {
  std::string finalString = "";

  for (auto &tk : tokens) {
    finalString.append("\"" + tk + "\"\n");
  }
  
  return finalString;
}


std::string vectorToString(std::vector<int> v) {
  if (v.empty())
    return "empty!";
    
  std::string finalString = "[";
  char buff[10];
  for (auto n : v) {
    snprintf(buff, sizeof(buff), "%2d, ", n);
    finalString.append(buff);
  }
  
  return finalString + "]";
}


std::string strToIntMapToString(std::map<std::string, int> map) {
  std::string finalString = "[";
  for (auto & pair : map) {
    finalString.append(pair.first + ": " + std::to_string(pair.second) + ", ");
  }
  return finalString + "]";
}


bool findErrorWith(std::string str, std::vector<std::string>& errors) {
  std::size_t foundAt;
  for (auto &error : errors) {
    foundAt =  error.find(str);
    if (foundAt != std::string::npos) {
      errors.erase(errors.begin() + foundAt);
      return true;
    }
  }
  
  return false;
}


std::string toLower(std::string str) {
  std::for_each(
    str.begin(), 
    str.end(), 
    [](char& c) { c = ::tolower(c); }
  );

  return str;
}


