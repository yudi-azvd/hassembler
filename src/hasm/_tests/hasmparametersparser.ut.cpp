#include <iostream>

#include "doctest.h"
#include "hasm/hasmparametersparser.h"


TEST_SUITE("hasm-hasmparametersparser") {


TEST_CASE("should get correct file names") {
  std::vector<std::string> args = {"a.asm", "b.asm"};

  HasmParametersParser parser(args);
  HasmParameters params = parser.run();

  std::vector<std::string> expectedFilenames = {"a.asm", "b.asm"};

  CHECK_EQ(expectedFilenames, params.filenames);
}


TEST_CASE("should get correct single file name even with -c flag") {
  std::vector<std::string> args = {"a.asm", "-c"};

  HasmParametersParser parser(args);
  HasmParameters params = parser.run();

  std::vector<std::string> expectedFilenames = {"a.asm"};

  CHECK_EQ(expectedFilenames, params.filenames);
}


TEST_CASE("should get correct file names even with -c flag") {
  std::vector<std::string> args = {"a.asm", "b.asm", "-c"};

  HasmParametersParser parser(args);
  HasmParameters params = parser.run();

  std::vector<std::string> expectedFilenames = {"a.asm", "b.asm"};

  CHECK_EQ(expectedFilenames, params.filenames);
}


TEST_CASE("should get correct file names even with -o flag") {
  std::vector<std::string> args = {"a.asm", "-o", "a.o"};

  HasmParametersParser parser(args);
  HasmParameters params = parser.run();

  std::vector<std::string> expectedFilenames = {"a.asm"};

  INFO("exp ", expectedFilenames);
  INFO("got ", params.filenames);
  CHECK_EQ(expectedFilenames, params.filenames);
}


TEST_CASE("should get correct output names with -o flag") {
  std::vector<std::string> args = {"a.asm", "-o", "a.o"};

  HasmParametersParser parser(args);
  HasmParameters params = parser.run();

  std::string expectedOutputName = {"a.o"};

  CHECK_EQ(expectedOutputName, params.outputFilename);
}


TEST_CASE("should detect dump hasm data flag") {
  std::vector<std::string> args = {"fatorial.asm", "triangle.asm", "-dh"};

  HasmParametersParser parser(args);
  HasmParameters params = parser.run();

  CHECK(params.dumpHasmData);
}


TEST_CASE("should throw exception when input name is the same as output name") {
  std::vector<std::string> args = {"a.asm", "-o", "a.asm"};

  HasmParametersParser parser(args);
  CHECK_THROWS_WITH_AS(parser.run(),
    "error: output name is same as input name",
    HasmParameterException
  );
}


TEST_CASE("should throw exception when no output name is given using -o flag") {
  std::vector<std::string> args = {"a.asm", "-o"};

  HasmParametersParser parser(args);
  CHECK_THROWS_WITH_AS(parser.run(),
    "error: missing file name after '-o'",
    HasmParameterException);
}


TEST_CASE("should throw exception when given multiple input files while  using"
  " -o flag") {

  std::vector<std::string> args = {"a.asm", "b.asm", "-o", "c.o"};

  HasmParametersParser parser(args);
  CHECK_THROWS_WITH_AS(parser.run(),
    "error: not allowed to use '-o' with multiple input files",
    HasmParameterException);
}


TEST_CASE("should throw exception when no input files are given") {
  std::vector<std::string> args = {};

  HasmParametersParser parser(args);
  CHECK_THROWS_WITH_AS(parser.run(),
    "error: no input files",
    HasmParameterException);
}


TEST_CASE("should throw exception when no input files are given while using -o")
{
  std::vector<std::string> args = {"-o", "outfile"};

  HasmParametersParser parser(args);
  CHECK_THROWS_WITH_AS(parser.run(),
    "error: no input files",
    HasmParameterException);
}

}
