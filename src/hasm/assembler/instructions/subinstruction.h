#ifndef SUBINSTRUCTION_H_INCLUDED
#define SUBINSTRUCTION_H_INCLUDED

#include "instruction.h"


class SubInstruction : public Instruction {
public:
  SubInstruction() {
    name = "sub";
    opcode = 2;
    size = 2;
  }

  ~SubInstruction() {}
};


#endif // SUBINSTRUCTION_H_INCLUDED
