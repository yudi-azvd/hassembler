#include "hasm.h"


Hasm::Hasm() { }


Hasm::~Hasm() {
  delete assembler;
  // delete linker;
  // delete outputGen;
}


Hasm::Hasm(std::vector<std::string> args) {
  HasmParametersParser parser(args);
  parameters = parser.run();
}


void Hasm::run() {
  /*
  HasmData hasmData(parameters);

  inputFiles = new InputFiles(hasmData);
  inputFiles.read(); // Deve adicionar Sources em hasmData.
                     // Deve também lançar exceção se existirem arquivos
                     // de tipos diferentes.

  if (inputFiles.areAssemblyFiles()) {
    assembler = new Assembler(hasmData);
    assembler->assemble();
  }

  if (hasmData.mustLink()) {
    linker = new Linker(hasmData);
    linker->link()
  }

  outputGen = new OutputGenerator(hasmData);
  outputGen->run();
  */
}
