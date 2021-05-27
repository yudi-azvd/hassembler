#include "definitionstable.hpp"


void DefinitionsTable::add(std::string name, int position) {
  table[name] = position;
}


bool DefinitionsTable::has(std::string name) {
  bool found = table.find(name) != table.end();
  return found;
}


int DefinitionsTable::getPositionOf(std::string name) {
  for (auto nameAndPostion : table) {
    if (nameAndPostion.first == name)
      return nameAndPostion.second;
  }

  return 0;
}

std::map<std::string, int>& DefinitionsTable::getTable() {
  return table;
}


std::ostream& operator<<(std::ostream& os, const DefinitionsTable& dt) {
  os << "[";
  for (auto pair : dt.table) os << pair.first << ": " << pair.second << ", ";
  return os << "]";
}

