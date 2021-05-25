#include "correctionfactortable.hpp"

void CorrectionFactorTable::add(std::string name, int size) {
  table.push_back(std::make_pair(name, accumulator));
  lastSize = size;
  accumulator += lastSize;
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