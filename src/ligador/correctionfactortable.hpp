#ifndef CORRECTIONFACTORTABLE_H_INCLUDED
#define CORRECTIONFACTORTABLE_H_INCLUDED

#include <iostream>
#include <sstream>
#include <vector>

class CorrectionFactorTable {
public:
  CorrectionFactorTable() {}

  void add(std::string name, int size);

  int getSizeOf(std::string name);

  std::string toString();

private:
  std::vector<std::pair<std::string, int>> table;
};

#endif // CORRECTIONFACTORTABLE_H_INCLUDED