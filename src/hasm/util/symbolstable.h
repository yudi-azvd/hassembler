#ifndef SYMBOLSTABLE_H_INCLUDED
#define SYMBOLSTABLE_H_INCLUDED

#include <iostream>
#include <map>


class SymbolsTable {
public:
  SymbolsTable() {};

  ~SymbolsTable() {};

  void add(std::string name, int position, bool isExternal=false);

  bool has(std::string name);

  int getPositionOf(std::string name);

  bool isExternal(std::string name);

  friend bool operator==(const SymbolsTable& lhs, const SymbolsTable& rhs) {
    return lhs.table == rhs.table;
  }

  friend std::ostream& operator<<(std::ostream& os, const SymbolsTable& st) {
    os << "[" << std::boolalpha; // habilita escrita true e false
    for (auto& pair : st.table) {
      os << "(" << pair.first << ", "
        << pair.second.position
        << ", ext=" << pair.second.isExternal << ") ";
    }

    return os << "]\n"; // deixa '\n' aqui?
  }

private:
  struct Symbol {
    int position;
    bool isExternal;

    friend bool operator==(const Symbol& lhs, const Symbol& rhs) {
      return (lhs.isExternal == rhs.isExternal)
        && (lhs.position == rhs.position);
    }
  };

  std::map<std::string, Symbol> table;

  std::map<std::string, Symbol>::iterator iter;
};


#endif // SYMBOLSTABLE_H_INCLUDED
