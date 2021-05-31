#include "hasm.h"


Hasm::Hasm() { }


Hasm::~Hasm() {
  delete assembler;
  delete hasmData;
  // delete linker;
  // delete outputGen;
}


Hasm::Hasm(std::vector<std::string> args) {
  HasmParametersParser parser(args);
  parameters = parser.run();
  hasmData = new HasmData(parameters);
}


void Hasm::run() {

  /*
  inputFiles = new InputFiles(hasmData);
  inputFiles.read(); // Deve adicionar Sources em hasmData.assemblerData.
                     // Deve também lançar exceção se existirem arquivos
                     // de tipos diferentes.

  if (inputFiles.areAssemblyFiles()) {
    assembler = new TwoPassesAssembler(hasmData);
    assembler->run();
  }

  if (hasmData.mustLink()) {
    linker = new Linker(hasmData);
    linker->run()
  }

  outputGen = new OutputGenerator(hasmData);
  outputGen->run();
  */
}
