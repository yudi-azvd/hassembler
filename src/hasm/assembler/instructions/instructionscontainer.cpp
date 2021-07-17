#include "instructionscontainer.h"

InstructionsContainer::InstructionsContainer() {
  registerInstructions();
}


InstructionsContainer::~InstructionsContainer() {}


bool InstructionsContainer::has(std::string instructionName) {
  return container.find(instructionName) != container.end();
}


uint16_t InstructionsContainer::getSizeOf(std::string instructionName) {
  if (!has(instructionName)) {
    // return? exception?
  }

  return container[instructionName].getSize();
}


uint16_t InstructionsContainer::getOpcodeOf(std::string instructionName) {
  if (!has(instructionName)) {
    // return? exception?
  }
  return container[instructionName].getOpcode();
}


void InstructionsContainer::registerInstructions() {
  container[AddInstruction().getName()] = AddInstruction();
  container[SubInstruction().getName()] = SubInstruction();
  container[MulInstruction().getName()] = MulInstruction();
  container[DivInstruction().getName()] = DivInstruction();
  container[JmpInstruction().getName()] = JmpInstruction();
  container[JmpnInstruction().getName()] = JmpnInstruction();
  container[JmppInstruction().getName()] = JmppInstruction();
  container[JmpzInstruction().getName()] = JmpzInstruction();
  container[CopyInstruction().getName()] = CopyInstruction();
  container[LoadInstruction().getName()] = LoadInstruction();
  container[StoreInstruction().getName()] = StoreInstruction();
  container[InputInstruction().getName()] = InputInstruction();
  container[OutputInstruction().getName()] = OutputInstruction();
  container[StopInstruction().getName()] = StopInstruction();
}
