#ifndef COPYINSTRUCTION_H_INCLUDED
#define COPYINSTRUCTION_H_INCLUDED

#include "instruction.h"


class CopyInstruction : public Instruction {
public:
  CopyInstruction() {
    name = "copy";
    opcode = 9;
    size = 3;
  }

  ~CopyInstruction() {}
};


#endif // COPYINSTRUCTION_H_INCLUDED
