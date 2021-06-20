#ifndef JMPZINSTRUCTION_H_INCLUDED
#define JMPZINSTRUCTION_H_INCLUDED

#include "instruction.h"


class JmpzInstruction : public Instruction {
public:
  JmpzInstruction() {
    name = "jmpz";
    opcode = 8;
    size = 2;
  }

  ~JmpzInstruction() {}
};


#endif // JMPZINSTRUCTION_H_INCLUDED
