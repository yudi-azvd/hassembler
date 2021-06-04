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
  iter = table.find(name);
  if (iter == table.end())
    throw std::runtime_error("error: symbol '"+name+"' not found");
  return iter->second.position;
}


bool SymbolsTable::isExternal(std::string name) {
  iter = table.find(name);
  if (iter == table.end())
    throw std::runtime_error("error: symbol '"+name+"' not found");
  return iter->second.isExternal;
}
