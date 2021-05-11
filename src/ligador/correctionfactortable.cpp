#include "correctionfactortable.hpp"

void CorrectionFactorTable::add(std::string name, int size) {
  int lastSize = table.empty() ? 0 : table.back().second;
  table.push_back(std::make_pair(name, lastSize+size));
}


int CorrectionFactorTable::getSizeOf(std::string name) {
  for (auto item : table) {
    if (item.first == name)
      return item.second;
  }

  return 0;
}


std::string CorrectionFactorTable::toString() {
  std::stringstream ss; ss << "[";

  for (auto item : table) {
    ss << item.first << ": " << item.second << ", ";
  }
  ss << "]";
  return ss.str();
}