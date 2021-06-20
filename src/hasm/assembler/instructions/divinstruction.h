#ifndef DIVINSTRUCTION_H_INCLUDED
#define DIVINSTRUCTION_H_INCLUDED

#include "instruction.h"


class DivInstruction : public Instruction {
public:
  DivInstruction() {
    name = "div";
    opcode = 4;
    size = 2;
  }

  ~DivInstruction() {}
};


#endif // DIVINSTRUCTION_H_INCLUDED
