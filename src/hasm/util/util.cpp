#include "util.h"

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


bool isNumber(std::string str) {
  if (str[0] != '-' && str[0] != '+' && !std::isdigit(str[0])) {
    return false;
  }

  for (size_t i = 1; i < str.length(); ++i) {
    if (!std::isdigit(str[i])) {
      return false;
    }
  }

  return true;
}


std::vector<std::string> stringVectorLowerCased(const std::vector<std::string> strs) {
  std::vector<std::string> lowered;
  lowered.reserve(strs.size());

  std::transform(
    strs.begin(),
    strs.end(),
    std::back_inserter(lowered),
    [](const std::string& in) {
      std::string out;
      out.reserve(in.size());
      std::transform(in.begin(), in.end(), std::back_inserter(out), ::tolower);
      return out;
    }
  );

  return lowered;
}


bool findInVector(std::vector<std::string> vec, std::string value) {
  for (auto item : vec) {
    if (item == value)
      return true;
  }

  return false;
}
