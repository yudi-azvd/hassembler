#include <iostream>

#include "doctest/doctest.h"
#include "util/commandlineparser.h"
#include "util/assemblyoptions.h"


TEST_CASE("should get correct single file name even with -c flag") {
  int argc = 3;
  const char* argv[] = {"./hasm", "a.asm", "-c"};

  CommandLineParser parser(argc, argv);

  AssemblyOptions asmOptions = parser.run();

  std::vector<std::string> expectedFileNames = {"a.asm"};

  CHECK_EQ(expectedFileNames, asmOptions.fileNames);
}


TEST_CASE("should get correct file names") {
  int argc = 3;
  const char* argv[] = {"./hasm", "a.asm", "b.asm"};

  CommandLineParser parser(argc, argv);

  AssemblyOptions asmOptions = parser.run();

  std::vector<std::string> expectedFileNames = {"a.asm", "b.asm"};

  CHECK_EQ(expectedFileNames, asmOptions.fileNames);
}


TEST_CASE("should get correct file names even with -c flag") {
  int argc = 4;
  const char* argv[] = {"./hasm", "a.asm", "b.asm", "-c"};

  CommandLineParser parser(argc, argv);

  AssemblyOptions asmOptions = parser.run();

  std::vector<std::string> expectedFileNames = {"a.asm", "b.asm"};

  CHECK_EQ(expectedFileNames, asmOptions.fileNames);
}


TEST_CASE("should get correct file names even with -o flag") {
  int argc = 4;
  const char* argv[] = {"./hasm", "a.asm", "-o", "a.o"};

  CommandLineParser parser(argc, argv);

  AssemblyOptions asmOptions = parser.run();

  std::vector<std::string> expectedFileNames = {"a.asm"};

  INFO("exp ", expectedFileNames);
  INFO("got ", asmOptions.fileNames);
  CHECK_EQ(expectedFileNames, asmOptions.fileNames);
}


TEST_CASE("should get correct output names with -o flag") {
  int argc = 4;
  const char* argv[] = {"./hasm", "a.asm", "-o", "a.o"};

  CommandLineParser parser(argc, argv);

  AssemblyOptions asmOptions = parser.run();

  std::string expectedOutputName = {"a.o"};

  CHECK_EQ(expectedOutputName, asmOptions.outputFileName);
}


TEST_CASE("should throw exception when input name is the same as output name") {
  int argc = 4;
  const char* argv[] = {"./hasm", "a.asm", "-o", "a.asm"};

  CommandLineParser parser(argc, argv);

  CHECK_THROWS_WITH(parser.run(), "Nome de saída é igual ao nome de entrada");
}


TEST_CASE("should throw exception when no output name is given using -o flag") {
  int argc = 3;
  const char* argv[] = {"./hasm", "a.asm", "-o"};

  CommandLineParser parser(argc, argv);

  CHECK_THROWS_WITH(parser.run(), "Falta o nome do arquivo depois de '-o'");
}


TEST_CASE("should throw exception when given multiple input files while  using -o flag") {
  int argc = 5;
  const char* argv[] = {"./hasm", "a.asm", "b.asm", "-o", "c.o"};

  CommandLineParser parser(argc, argv);

  CHECK_THROWS_WITH(parser.run(), "Não é permitido usar '-o' com mútiplos arquivos");
}


TEST_CASE("should throw exception when no input files are given") {
  int argc = 1;
  const char* argv[] = {"./hasm"};

  CommandLineParser parser(argc, argv);

  CHECK_THROWS_WITH(parser.run(), "Não há arquivos de entrada");
}


TEST_CASE("should throw exception when no input files are given while using -o") {
  int argc = 1;
  const char* argv[] = {"./hasm", "-o", "outfile"};

  CommandLineParser parser(argc, argv);

  CHECK_THROWS_WITH(parser.run(), "Não há arquivos de entrada");
}


TEST_CASE("should throw exception when using wrong constructor") {
  try {
    CommandLineParser parser;
  }
  catch(const std::invalid_argument& e) {
    std::string exceptionMessage(e.what());
    CHECK("default constructor should not be used. Use "
      "'CommandLineParser(int argc, const char* argv[])' instead"
      == exceptionMessage);
  }
}



/*

hasm a.asm
    compilar e ligar

hasm a.asm -o a
    compilar, ligar e o arquivo executável se chama "a"

hasm -c a.asm b.asm -o programa
    erro: não é permitido usar -o com múltiplos programas

hasm a.asm b.asm c.asm
    compilar e ligar os tres arquivos

hasm -c a.asm b.asm c.asm
    apenas compilar os três arquivos


*/