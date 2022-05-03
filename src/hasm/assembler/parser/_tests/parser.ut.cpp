#include <iostream>
#include <vector>

#include "doctest.h"
#include "assembler/assemblyerror.h"
#include "assembler/assemblydata.h"
#include "assembler/parser/parser.h"


TEST_SUITE_BEGIN("assembler-parser");


TEST_CASE("parser") {
  AssemblyData assemblyData;
  Parser parser;
  parser.setAssemblyData(&assemblyData);
  parser.setFilename("");
  parser.setLineCounter(0);
  std::vector<std::string> tokens;

  SUBCASE("should get all empty when line is empty") {
    tokens = {};

    parser.runOn(tokens);

    CHECK(parser.getLabel().empty());
    CHECK(parser.getOperation().empty());
    CHECK(parser.getOperand1().empty());
    CHECK(parser.getOperand2().empty());
  }

  SUBCASE("should get label") {
    tokens = {"label", ":", "const", "3"};
    auto expectedLabel = "label";

    parser.runOn(tokens);
    auto gotLabel = parser.getLabel();

    CHECK(expectedLabel == gotLabel);
  }

  SUBCASE("should throw missing label error") {
    tokens = {":", "const", "3"};
    parser.runOn(tokens);

    REQUIRE(assemblyData.getErrors().size() == 1);
    CHECK(
      "assembly error [](0): missing label before ':'"
      == assemblyData.getErrors().back().getMessage()
    );
  }

  // SUBCASE("should throw missing label error") {
  //   tokens = {":", "const", "3"};

  //   try {
  //     parser.runOn(tokens);
  //     FAIL("should've thrown missing label");
  //   }
  //   catch (ParserException& e) {
  //     REQUIRE(e.getErrorCodes().size() == 1);
  //     CHECK_EQ(e.getErrorCodes().back(), ParserException::ErrorCode::MISSING_LABEL);
  //   }
  // }

  SUBCASE("should get operation") {
    tokens = {"label", ":", "const", "3"};

    std::string expectedOperation = "const";

    parser.runOn(tokens);
    auto gotOperation = parser.getOperation();

    CHECK(expectedOperation == gotOperation);
  }


  SUBCASE("should get instruction as operation with no label") {
    tokens = {"add", "label"};

    std::string expectedOperation = "add";

    parser.runOn(tokens);
    auto gotOperation = parser.getOperation();

    CHECK(expectedOperation == gotOperation);
  }


  SUBCASE("should get COPY as operation with no label") {
    tokens = {"copy", "label1", ",", "label2"};

    std::string expectedOperation = "copy";

    parser.runOn(tokens);
    auto gotOperation = parser.getOperation();

    CHECK(expectedOperation == gotOperation);
  }


  SUBCASE("should get STOP as operation with no label") {
    tokens = {"stop"};

    std::string expectedOperation = "stop";

    parser.runOn(tokens);
    auto gotOperation = parser.getOperation();

    CHECK(expectedOperation == gotOperation);
  }


  SUBCASE("should get STOP as operation with label") {
    tokens = {"finish", ":", "stop"};

    std::string expectedOperation = "stop";

    parser.runOn(tokens);
    auto gotOperation = parser.getOperation();

    CHECK(expectedOperation == gotOperation);
    CHECK("finish" == parser.getLabel());
  }


  SUBCASE("should get empty operation when label is alone") {
    tokens = {"label_is_alone", ":"};

    parser.runOn(tokens);
    auto gotOperation = parser.getOperation();

    CHECK(gotOperation.empty());
  }


  SUBCASE("should get empty operands when label is alone") {
    tokens = {"label_is_alone", ":"};

    parser.runOn(tokens);

    CHECK("" == parser.getOperand1());
    CHECK("" == parser.getOperand2());
  }


  SUBCASE("should get first operand with directive as operation") {
    tokens = {"label", ":",  "const",  "3"};

    parser.runOn(tokens);

    CHECK("3" == parser.getOperand1());
  }


  SUBCASE("should get operands with COPY as operation not using comma") {
    tokens = {"label", ":",  "copy",  "label1", "label2"};

    parser.runOn(tokens);

    CHECK("label1" == parser.getOperand1());
    CHECK("label2" == parser.getOperand2());
  }


  SUBCASE("should get operands with COPY as operation using comma") {
    tokens = {"label", ":",  "copy",  "label1", ",", "label2"};

    parser.runOn(tokens);

    CHECK("label1" == parser.getOperand1());
    CHECK("label2" == parser.getOperand2());
  }


  SUBCASE("should get oprands with COPY as operation without comma") {
    tokens = {"label", ":",  "copy",  "label1", "label2"};

    parser.runOn(tokens);

    CHECK("label1" == parser.getOperand1());
    CHECK("label2" == parser.getOperand2());
  }
}


TEST_SUITE_END();
