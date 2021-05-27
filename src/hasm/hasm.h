#ifndef HASM_H_INCLUDED
#define HASM_H_INCLUDED

#include <iostream>
#include <vector>

#include "assembler/assembler.h"
#include "hasmparametersparser.h"


class Hasm {
public:
  Hasm();

  Hasm(int argc, const char** argv);

  ~Hasm();

  void run();

private:
  HasmParameters parameters;

  Assembler* assembler;
};

#endif // HASM_H_INCLUDED
