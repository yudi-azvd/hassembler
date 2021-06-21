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

  SUBCASE("jmpn") {
    CHECK(instructionContainer.has("jmpn"));
    CHECK_EQ(6, instructionContainer.getOpcodeOf("jmpn"));
    CHECK_EQ(2, instructionContainer.getSizeOf("jmpn"));
  }

  SUBCASE("jmpp") {
    CHECK(instructionContainer.has("jmpp"));
    CHECK_EQ(7, instructionContainer.getOpcodeOf("jmpp"));
    CHECK_EQ(2, instructionContainer.getSizeOf("jmpp"));
  }

  SUBCASE("jmpz") {
    CHECK(instructionContainer.has("jmpz"));
    CHECK_EQ(8, instructionContainer.getOpcodeOf("jmpz"));
    CHECK_EQ(2, instructionContainer.getSizeOf("jmpz"));
  }

  SUBCASE("copy") {
    CHECK(instructionContainer.has("copy"));
    CHECK_EQ(9, instructionContainer.getOpcodeOf("copy"));
    CHECK_EQ(3, instructionContainer.getSizeOf("copy"));
  }

  SUBCASE("load") {
    CHECK(instructionContainer.has("load"));
    CHECK_EQ(10, instructionContainer.getOpcodeOf("load"));
    CHECK_EQ(2, instructionContainer.getSizeOf("load"));
  }

  SUBCASE("store") {
    CHECK(instructionContainer.has("store"));
    CHECK_EQ(11, instructionContainer.getOpcodeOf("store"));
    CHECK_EQ(2, instructionContainer.getSizeOf("store"));
  }

  SUBCASE("input") {
    CHECK(instructionContainer.has("input"));
    CHECK_EQ(12, instructionContainer.getOpcodeOf("input"));
    CHECK_EQ(2, instructionContainer.getSizeOf("input"));
  }

  SUBCASE("output") {
    CHECK(instructionContainer.has("output"));
    CHECK_EQ(13, instructionContainer.getOpcodeOf("output"));
    CHECK_EQ(2, instructionContainer.getSizeOf("output"));
  }

  SUBCASE("stop") {
    CHECK(instructionContainer.has("stop"));
    CHECK_EQ(14, instructionContainer.getOpcodeOf("stop"));
    CHECK_EQ(1, instructionContainer.getSizeOf("stop"));
  }
}


TEST_SUITE_END();
