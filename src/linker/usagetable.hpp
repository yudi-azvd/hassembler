#ifndef USAGETABLE_H_INCLUDED
#define USAGETABLE_H_INCLUDED

#include <iostream>
#include <vector>

class UsageTable {
public:
  UsageTable() {}

  ~UsageTable() {}

  void add(std::string name, int position);

  int getPositionOf(std::string name);

  bool has(std::string name);

  friend std::ostream& operator<<(std::ostream& os, const UsageTable& ut) {
    os << "[";
    for (auto positionAndName : ut.table) {
      os << positionAndName.second << ": " << positionAndName.first << ", ";
    }
    os << "]";
    return os;
  }

  // ideal seria fazer um iterador
  std::vector<std::pair<int, std::string>>& getTable();

private:
  // struct Item {
  //   int position;
  //   std::string name;
  // };

  // std::vector<Item> table;

  std::vector<std::pair<int, std::string>> table;
};

#endif // USAGETABLE_H_INCLUDED
