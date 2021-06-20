#ifndef JMPPINSTRUCTION_H_INCLUDED
#define JMPPINSTRUCTION_H_INCLUDED

#include "instruction.h"


class JmppInstruction : public Instruction {
public:
  JmppInstruction() {
    name = "jmpp";
    opcode = 7;
    size = 2;
  }

  ~JmppInstruction() {}
};


#endif // JMPPINSTRUCTION_H_INCLUDED
