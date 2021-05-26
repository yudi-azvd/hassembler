#include <iostream>

#include "doctest/doctest.h"
#include "util/commandlineparser.h"


TEST_CASE("command line parser") {
  const char* argv[] = {"./hasm", "a.asm", "b.asm"};

  CommandLineParser parser(argv);

  parser.getFilesNames();

  CHECK_FALSE(parser.getCompileOnly());
  parser.getCompileOnly();


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