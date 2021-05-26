#include <iostream>

#include "doctest/doctest.h"
#include "util/commandlineparser.h"
#include "util/assemblyoptions.h"


TEST_CASE("command line parser get correct file names") {
  int argc = 3;
  const char* argv[] = {"./hasm", "a.asm", "b.asm"};

  CommandLineParser parser(argc, argv);

  AssemblyOptions asmOptions = parser.getAssemblyOptions();

  std::vector<std::string> expectedFileNames = {"a.asm", "b.asm"};

  CHECK_EQ(expectedFileNames, asmOptions.fileNames);
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