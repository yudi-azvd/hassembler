#ifndef OUTPUTINSTRUCTION_H_INCLUDED
#define OUTPUTINSTRUCTION_H_INCLUDED

#include "instruction.h"


class OutputInstruction : public Instruction {
public:
  OutputInstruction() {
    name = "output";
    opcode = 13;
    size = 2;
  }

  ~OutputInstruction() {}
};


#endif // OUTPUTINSTRUCTION_H_INCLUDED
