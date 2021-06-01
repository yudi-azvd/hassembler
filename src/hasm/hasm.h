#ifndef HASM_H_INCLUDED
#define HASM_H_INCLUDED

#include <iostream>
#include <vector>

#include "hasmparametersparser.h"
#include "assembler/assembler.h"
#include "input/input.h"
#include "assembler/oldassembler.h"


class Hasm {
public:
  Hasm();

  Hasm(std::vector<std::string> args);

  ~Hasm();

  void run();

private:
  HasmParameters parameters;

  HasmData* hasmData = nullptr;

  OldAssembler* oldAssembler = nullptr;

  Input* input = nullptr;

  Assembler* assembler = nullptr;

};


#endif // HASM_H_INCLUDED
