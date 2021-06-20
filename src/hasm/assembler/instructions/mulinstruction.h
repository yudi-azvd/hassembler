#ifndef MULINSTRUCTION_H_INCLUDED
#define MULINSTRUCTION_H_INCLUDED

#include "instruction.h"


class MulInstruction : public Instruction {
public:
  MulInstruction() {
    name = "mul";
    opcode = 3;
    size = 2;
  }

  ~MulInstruction() {}
};


#endif // MULINSTRUCTION_H_INCLUDED
