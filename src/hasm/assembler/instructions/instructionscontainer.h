#ifndef INSTRUCTIONCONTAINER_H_INCLUDED
#define INSTRUCTIONCONTAINER_H_INCLUDED

#include <iostream>
#include <map>

#include "instruction.h"
#include "allinstructions.h"


class InstructionsContainer {
public:
  InstructionsContainer();

  ~InstructionsContainer();

  bool has(std::string instructionName);

  uint16_t getSizeOf(std::string instructionName);

  uint16_t getOpcodeOf(std::string instructionName);

private:
  std::map<std::string, Instruction> container;

  void registerInstructions();
};


#endif // INSTRUCTIONCONTAINER_H_INCLUDED
