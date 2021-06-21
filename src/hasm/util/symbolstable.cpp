#include "symbolstable.h"


void SymbolsTable::add(std::string name, int position, bool isExternal) {
  Symbol s = {position, isExternal};
  table[name] = s;
}


bool SymbolsTable::has(std::string name) {
  iter = table.find(name);
  return iter != table.end();
}


int SymbolsTable::getPositionOf(std::string name) {
  return table.at(name).position;
}


bool SymbolsTable::isExternal(std::string name) {
  return table.at(name).isExternal;
}
