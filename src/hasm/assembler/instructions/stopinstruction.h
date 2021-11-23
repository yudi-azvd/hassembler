#ifndef STOPINSTRUCTION_H_INCLUDED
#define STOPINSTRUCTION_H_INCLUDED

#include "instruction.h"


class StopInstruction : public Instruction {
public:
  StopInstruction() {
    name = "stop";
    opcode = 14;
    size = 1;
  }

  ~StopInstruction() {}
};


#endif // STOPINSTRUCTION_H_INCLUDED
