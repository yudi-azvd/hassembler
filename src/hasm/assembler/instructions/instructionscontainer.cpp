#include "instructionscontainer.h"

InstructionContainer::InstructionContainer() {
  registerInstructions();
}

InstructionContainer::~InstructionContainer() {}


bool InstructionContainer::has(std::string instructionName) {
  return container.find(instructionName) != container.end();
}


uint16_t InstructionContainer::getSizeOf(std::string instructionName) {
  if (!has(instructionName)) {
    // return? exception?
  }

  return container[instructionName].getSize();
}


uint16_t InstructionContainer::getOpcodeOf(std::string instructionName) {
  if (!has(instructionName)) {
    // return? exception?
  }
  return container[instructionName].getOpcode();
}


void InstructionContainer::registerInstructions() {
  container[AddInstruction().getName()] = AddInstruction();
  container[SubInstruction().getName()] = SubInstruction();
  container[MulInstruction().getName()] = MulInstruction();
  container[DivInstruction().getName()] = DivInstruction();
  container[JmpInstruction().getName()] = JmpInstruction();
  container[JmpnInstruction().getName()] = JmpnInstruction();
  container[JmppInstruction().getName()] = JmppInstruction();
  container[JmpzInstruction().getName()] = JmpzInstruction();
  container[LoadInstruction().getName()] = LoadInstruction();
  container[StoreInstruction().getName()] = StoreInstruction();
  container[InputInstruction().getName()] = InputInstruction();
  container[OutputInstruction().getName()] = OutputInstruction();
  container[StopInstruction().getName()] = StopInstruction();
}

