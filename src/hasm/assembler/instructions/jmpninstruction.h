#ifndef JMPNINSTRUCTION_H_INCLUDED
#define JMPNINSTRUCTION_H_INCLUDED

#include "instruction.h"


class JmpnInstruction : public Instruction {
public:
  JmpnInstruction() {
    name = "jmpn";
    opcode = 6;
    size = 2;
  }

  ~JmpnInstruction() {}
};


#endif // JMPNINSTRUCTION_H_INCLUDED
