#ifndef HASM_H_INCLUDED
#define HASM_H_INCLUDED

#include <iostream>
#include <vector>

#include "assembler/assembler.h"
#include "hasmparametersparser.h"


class Hasm {
public:
  Hasm();

  Hasm(std::vector<std::string> args);

  ~Hasm();

  void run();

private:
  HasmParameters parameters;

  HasmData* hasmData;

  Assembler* assembler;
};

#endif // HASM_H_INCLUDED
