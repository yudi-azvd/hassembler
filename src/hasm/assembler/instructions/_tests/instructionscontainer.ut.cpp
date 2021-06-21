#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/instructions/instructionscontainer.h"


TEST_SUITE_BEGIN("assembler-instructionscontainer");


TEST_CASE("instruction container has instructions") {
  InstructionContainer instructionContainer;

  CHECK_FALSE(instructionContainer.has("non-existing-instruction"));

  SUBCASE("add") {
    CHECK(instructionContainer.has("add"));
    CHECK_EQ(1, instructionContainer.getOpcodeOf("add"));
    CHECK_EQ(2, instructionContainer.getSizeOf("add"));
  }

  SUBCASE("sub") {
    CHECK(instructionContainer.has("sub"));
    CHECK_EQ(2, instructionContainer.getOpcodeOf("sub"));
    CHECK_EQ(2, instructionContainer.getSizeOf("sub"));
  }

  SUBCASE("mul") {
    CHECK(instructionContainer.has("mul"));
    CHECK_EQ(3, instructionContainer.getOpcodeOf("mul"));
    CHECK_EQ(2, instructionContainer.getSizeOf("mul"));
  }

  SUBCASE("div") {
    CHECK(instructionContainer.has("div"));
    CHECK_EQ(4, instructionContainer.getOpcodeOf("div"));
    CHECK_EQ(2, instructionContainer.getSizeOf("div"));
  }

  SUBCASE("jmp") {
    CHECK(instructionContainer.has("jmp"));
    CHECK_EQ(5, instructionContainer.getOpcodeOf("jmp"));
    CHECK_EQ(2, instructionContainer.getSizeOf("jmp"));
  }
}


// TEST_CASE("instruction cont. sub") {
//   Instruction instruction = SubInstruction();
//   CHECK_EQ(2, instruction.getOpcode());
//   CHECK_EQ("sub", instruction.getName());
//   CHECK_EQ(2, instruction.getSize());
// }


// TEST_CASE("instruction cont. mul") {
//   Instruction instruction = MulInstruction();
//   CHECK_EQ(3, instruction.getOpcode());
//   CHECK_EQ("mul", instruction.getName());
//   CHECK_EQ(2, instruction.getSize());
// }


// TEST_CASE("instruction cont. div") {
//   Instruction instruction = DivInstruction();
//   CHECK_EQ(4, instruction.getOpcode());
//   CHECK_EQ("div", instruction.getName());
//   CHECK_EQ(2, instruction.getSize());
// }


// TEST_CASE("instruction cont. jmp") {
//   Instruction instruction = JmpInstruction();
//   CHECK_EQ(5, instruction.getOpcode());
//   CHECK_EQ("jmp", instruction.getName());
//   CHECK_EQ(2, instruction.getSize());
// }


// TEST_CASE("instruction cont. jmpn") {
//   Instruction instruction = JmpnInstruction();
//   CHECK_EQ(6, instruction.getOpcode());
//   CHECK_EQ("jmpn", instruction.getName());
//   CHECK_EQ(2, instruction.getSize());
// }


// TEST_CASE("instruction cont. jmpp") {
//   Instruction instruction = JmppInstruction();
//   CHECK_EQ(7, instruction.getOpcode());
//   CHECK_EQ("jmpp", instruction.getName());
//   CHECK_EQ(2, instruction.getSize());
// }


// TEST_CASE("instruction cont. jmpz") {
//   Instruction instruction = JmpzInstruction();
//   CHECK_EQ(8, instruction.getOpcode());
//   CHECK_EQ("jmpz", instruction.getName());
//   CHECK_EQ(2, instruction.getSize());
// }


// TEST_CASE("instruction cont. copy") {
//   Instruction instruction = CopyInstruction();
//   CHECK_EQ(9, instruction.getOpcode());
//   CHECK_EQ("copy", instruction.getName());
//   CHECK_EQ(3, instruction.getSize());
// }


// TEST_CASE("instruction cont. load") {
//   Instruction instruction = LoadInstruction();
//   CHECK_EQ(10, instruction.getOpcode());
//   CHECK_EQ("load", instruction.getName());
//   CHECK_EQ(2, instruction.getSize());
// }


// TEST_CASE("instruction cont. store") {
//   Instruction instruction = StoreInstruction();
//   CHECK_EQ(11, instruction.getOpcode());
//   CHECK_EQ("store", instruction.getName());
//   CHECK_EQ(2, instruction.getSize());
// }


// TEST_CASE("instruction cont. input") {
//   Instruction instruction = InputInstruction();
//   CHECK_EQ(12, instruction.getOpcode());
//   CHECK_EQ("input", instruction.getName());
//   CHECK_EQ(2, instruction.getSize());
// }


// TEST_CASE("instruction cont. output") {
//   Instruction instruction = OutputInstruction();
//   CHECK_EQ(13, instruction.getOpcode());
//   CHECK_EQ("output", instruction.getName());
//   CHECK_EQ(2, instruction.getSize());
// }


// TEST_CASE("instruction cont. stop") {
//   Instruction instruction = StopInstruction();
//   CHECK_EQ(14, instruction.getOpcode());
//   CHECK_EQ("stop", instruction.getName());
//   CHECK_EQ(1, instruction.getSize());
// }


TEST_SUITE_END();
