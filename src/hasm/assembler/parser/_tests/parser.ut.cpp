#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/assemblyerror.h"
#include "assembler/parser/parser.h"


TEST_SUITE_BEGIN("assembler-parser");


TEST_CASE("should get all empty when line is empty") {
  Parser parser;
  std::vector<std::string> tokens = {};

  parser.runOn(tokens);

  CHECK(parser.getLabel().empty());
  CHECK(parser.getOperation().empty());
  CHECK(parser.getOperand1().empty());
  CHECK(parser.getOperand2().empty());
}


TEST_CASE("should get label") {
  Parser parser;
  std::vector<std::string> tokens
    = {"label", ":", "const", "3"};
  auto expectedLabel = "label";

  parser.runOn(tokens);
  auto gotLabel = parser.getLabel();

  CHECK(expectedLabel == gotLabel);
}


TEST_CASE("should throw missing label error") {
  Parser parser;
  std::vector<std::string> tokens
    = {":", "const", "3"};

  try {
    parser.runOn(tokens);
  }
  catch(AssemblyError& e) {
    CHECK(
      "assembly error [](0): missing label before ':'"
      == e.getMessage()
    );
  }

  FAIL_CHECK("something went wrong");
}


TEST_CASE("should get operation") {
  Parser parser;
  std::vector<std::string> tokens
    = {"label", ":", "const", "3"};

  std::string expectedOperation = "const";

  parser.runOn(tokens);
  auto gotOperation = parser.getOperation();

  CHECK(expectedOperation == gotOperation);
}


TEST_CASE("should get instruction as operation with no label") {
  Parser parser;
  std::vector<std::string> tokens
    = {"add", "label"};

  std::string expectedOperation = "add";

  parser.runOn(tokens);
  auto gotOperation = parser.getOperation();

  CHECK(expectedOperation == gotOperation);
}


TEST_CASE("should get COPY as operation with no label") {
  Parser parser;
  std::vector<std::string> tokens
    = {"copy", "label1", ",", "label2"};

  std::string expectedOperation = "copy";

  parser.runOn(tokens);
  auto gotOperation = parser.getOperation();

  CHECK(expectedOperation == gotOperation);
}


TEST_CASE("should get STOP as operation with no label") {
  Parser parser;
  std::vector<std::string> tokens
    = {"stop"};

  std::string expectedOperation = "stop";

  parser.runOn(tokens);
  auto gotOperation = parser.getOperation();

  CHECK(expectedOperation == gotOperation);
}


TEST_CASE("should get STOP as operation with label") {
  Parser parser;
  std::vector<std::string> tokens
    = {"finish", ":", "stop"};

  std::string expectedOperation = "stop";

  parser.runOn(tokens);
  auto gotOperation = parser.getOperation();

  CHECK(expectedOperation == gotOperation);
  CHECK("finish" == parser.getLabel());
}


TEST_CASE("should get empty operation when label is alone") {
  Parser parser;
  std::vector<std::string> tokens
    = {"label_is_alone", ":"};

  parser.runOn(tokens);
  auto gotOperation = parser.getOperation();

  CHECK(gotOperation.empty());
}


TEST_CASE("should get empty operands when label is alone") {
  Parser parser;
  std::vector<std::string> tokens
    = {"label_is_alone", ":"};

  parser.runOn(tokens);

  CHECK("" == parser.getOperand1());
  CHECK("" == parser.getOperand2());
}


TEST_CASE("should get first operand with directive as operation") {
  Parser parser;
  std::vector<std::string> tokens
    = {"label", ":",  "const",  "3"};

  parser.runOn(tokens);

  CHECK("3" == parser.getOperand1());
}


TEST_CASE("should get operands with COPY as operation not using comma") {
  Parser parser;
  std::vector<std::string> tokens
    = {"label", ":",  "copy",  "label1", "label2"};

  parser.runOn(tokens);

  CHECK("label1" == parser.getOperand1());
  CHECK("label2" == parser.getOperand2());
}


TEST_CASE("should get operands with COPY as operation using comma") {
  Parser parser;
  std::vector<std::string> tokens
    = {"label", ":",  "copy",  "label1", ",", "label2"};

  parser.runOn(tokens);

  CHECK("label1" == parser.getOperand1());
  CHECK("label2" == parser.getOperand2());
}


TEST_CASE("should not get second operand with COPY as operation") {
  Parser parser;
  std::vector<std::string> tokens
    = {"label", ":",  "copy",  "label1", ";", "label2"};

  parser.runOn(tokens);

  CHECK("label1" == parser.getOperand1());
  CHECK("label2" == parser.getOperand2());
}


TEST_SUITE_END();
