#ifndef JMPINSTRUCTION_H_INCLUDED
#define JMPINSTRUCTION_H_INCLUDED

#include "instruction.h"


class JmpInstruction : public Instruction {
public:
  JmpInstruction() {
    name = "jmp";
    opcode = 5;
    size = 2;
  }

  ~JmpInstruction() {}
};


#endif // JMPINSTRUCTION_H_INCLUDED
