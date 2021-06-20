#ifndef STOREINSTRUCTION_H_INCLUDED
#define STOREINSTRUCTION_H_INCLUDED

#include "instruction.h"


class StoreInstruction : public Instruction {
public:
  StoreInstruction() {
    name = "store";
    opcode = 11;
    size = 2;
  }

  ~StoreInstruction() {}
};


#endif // STOREINSTRUCTION_H_INCLUDED
