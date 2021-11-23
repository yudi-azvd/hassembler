#ifndef INPUTINSTRUCTION_H_INCLUDED
#define INPUTINSTRUCTION_H_INCLUDED

#include "instruction.h"


class InputInstruction : public Instruction {
public:
  InputInstruction() {
    name = "input";
    opcode = 12;
    size = 2;
  }

  ~InputInstruction() {}
};


#endif // INPUTINSTRUCTION_H_INCLUDED
