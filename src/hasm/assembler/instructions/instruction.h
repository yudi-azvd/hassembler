#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include <iostream>


class Instruction {
public:
  virtual ~Instruction() {};

  std::string getName() {
    return name;
  }

  uint16_t getOpcode() {
    return opcode;
  }

  uint16_t getSize() {
    return size;
  }

protected:
  std::string name;

  uint16_t opcode;

  uint16_t size;
};


#endif // INSTRUCTION_H_INCLUDED
