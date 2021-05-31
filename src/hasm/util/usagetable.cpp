#include "usagetable.h"

void UsageTable::add(std::string name, int position) {
  table.push_back(std::make_pair(position, name));
}


int UsageTable::getPositionOf(std::string name) {
  for (auto positionAndName : table) {
    if (positionAndName.second == name) {
      return positionAndName.first;
    }
  }

  // Seria melhor lançar exceção?
  return -1;
}


bool UsageTable::has(std::string name) {
  for (auto positionAndName : table) {
    if (positionAndName.second == name) {
      return true;
    }
  }

  return false;
}


std::vector<std::pair<int, std::string>>& UsageTable::getTable() {
  return table;
}

