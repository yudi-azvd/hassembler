#ifndef ADDINSTRUCTION_H_INCLUDED
#define ADDINSTRUCTION_H_INCLUDED

#include "instruction.h"


class AddInstruction : public Instruction {
public:
  AddInstruction() {
    name = "add";
    opcode = 1;
    size = 2;
  }

  ~AddInstruction() {}
};


#endif // ADDINSTRUCTION_H_INCLUDED
