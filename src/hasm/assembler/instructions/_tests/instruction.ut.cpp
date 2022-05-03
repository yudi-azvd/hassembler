#include <iostream>
#include <vector>

#include "doctest.h"
#include "assembler/instructions/instruction.h"
#include "assembler/instructions/allinstructions.h"


TEST_SUITE_BEGIN("assembler-instructions");


TEST_CASE("add instruction") {
  Instruction instruction = AddInstruction();
  CHECK_EQ(1, instruction.getOpcode());
  CHECK_EQ("add", instruction.getName());
  CHECK_EQ(2, instruction.getSize());
}


TEST_CASE("sub instruction") {
  Instruction instruction = SubInstruction();
  CHECK_EQ(2, instruction.getOpcode());
  CHECK_EQ("sub", instruction.getName());
  CHECK_EQ(2, instruction.getSize());
}


TEST_CASE("mul instruction") {
  Instruction instruction = MulInstruction();
  CHECK_EQ(3, instruction.getOpcode());
  CHECK_EQ("mul", instruction.getName());
  CHECK_EQ(2, instruction.getSize());
}


TEST_CASE("div instruction") {
  Instruction instruction = DivInstruction();
  CHECK_EQ(4, instruction.getOpcode());
  CHECK_EQ("div", instruction.getName());
  CHECK_EQ(2, instruction.getSize());
}


TEST_CASE("jmp instruction") {
  Instruction instruction = JmpInstruction();
  CHECK_EQ(5, instruction.getOpcode());
  CHECK_EQ("jmp", instruction.getName());
  CHECK_EQ(2, instruction.getSize());
}


TEST_CASE("jmpn instruction") {
  Instruction instruction = JmpnInstruction();
  CHECK_EQ(6, instruction.getOpcode());
  CHECK_EQ("jmpn", instruction.getName());
  CHECK_EQ(2, instruction.getSize());
}


TEST_CASE("jmpp instruction") {
  Instruction instruction = JmppInstruction();
  CHECK_EQ(7, instruction.getOpcode());
  CHECK_EQ("jmpp", instruction.getName());
  CHECK_EQ(2, instruction.getSize());
}


TEST_CASE("jmpz instruction") {
  Instruction instruction = JmpzInstruction();
  CHECK_EQ(8, instruction.getOpcode());
  CHECK_EQ("jmpz", instruction.getName());
  CHECK_EQ(2, instruction.getSize());
}


TEST_CASE("copy instruction") {
  Instruction instruction = CopyInstruction();
  CHECK_EQ(9, instruction.getOpcode());
  CHECK_EQ("copy", instruction.getName());
  CHECK_EQ(3, instruction.getSize());
}


TEST_CASE("load instruction") {
  Instruction instruction = LoadInstruction();
  CHECK_EQ(10, instruction.getOpcode());
  CHECK_EQ("load", instruction.getName());
  CHECK_EQ(2, instruction.getSize());
}


TEST_CASE("store instruction") {
  Instruction instruction = StoreInstruction();
  CHECK_EQ(11, instruction.getOpcode());
  CHECK_EQ("store", instruction.getName());
  CHECK_EQ(2, instruction.getSize());
}


TEST_CASE("input instruction") {
  Instruction instruction = InputInstruction();
  CHECK_EQ(12, instruction.getOpcode());
  CHECK_EQ("input", instruction.getName());
  CHECK_EQ(2, instruction.getSize());
}


TEST_CASE("output instruction") {
  Instruction instruction = OutputInstruction();
  CHECK_EQ(13, instruction.getOpcode());
  CHECK_EQ("output", instruction.getName());
  CHECK_EQ(2, instruction.getSize());
}


TEST_CASE("stop instruction") {
  Instruction instruction = StopInstruction();
  CHECK_EQ(14, instruction.getOpcode());
  CHECK_EQ("stop", instruction.getName());
  CHECK_EQ(1, instruction.getSize());
}


TEST_SUITE_END();
