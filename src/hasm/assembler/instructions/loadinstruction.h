#ifndef LOADINSTRUCTION_H_INCLUDED
#define LOADINSTRUCTION_H_INCLUDED

#include "instruction.h"


class LoadInstruction : public Instruction {
public:
  LoadInstruction() {
    name = "load";
    opcode = 10;
    size = 2;
  }

  ~LoadInstruction() {}
};


#endif // LOADINSTRUCTION_H_INCLUDED
