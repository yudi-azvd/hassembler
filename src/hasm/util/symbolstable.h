#ifndef SYMBOLSTABLE_H_INCLUDED
#define SYMBOLSTABLE_H_INCLUDED

#include <iostream>
#include <map>


class SymbolsTable {
private:
  struct Symbol {
    int position;
    bool isExternal;
  };

public:
  SymbolsTable() {};

  ~SymbolsTable() {};

  void add(std::string name, int position, bool isExternal=false);

  bool has(std::string name);

  int getPositionOf(std::string name);

  bool isExternal(std::string name);

private:
  std::map<std::string, Symbol> table;

  std::map<std::string, Symbol>::iterator iter;
};


#endif // SYMBOLSTABLE_H_INCLUDED
