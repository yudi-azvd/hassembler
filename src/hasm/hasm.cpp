#include "hasm.h"

#include "assembler/twopasses/twopassesassembler.h"


Hasm::Hasm() { }


Hasm::~Hasm() {
  delete oldAssembler;
  delete hasmData;
  delete assembler;
  delete input;
  // delete linker;
  // delete outputGen;
}


Hasm::Hasm(std::vector<std::string> args) {
  HasmParametersParser parser(args);
  parameters = parser.run();

  hasmData = new HasmData(parameters);
  oldAssembler = new OldAssembler(parameters.filenames);
  input = new Input(hasmData);
  assembler = new TwoPassesAssembler(hasmData->getAssemblyData());
}


void Hasm::run() {
  oldAssembler->assemble();

  /*
  input = new InputFiles(hasmData);
  input.readFiles(); // Deve adicionar Sources em hasmData.assemblyData.
                     // Deve também lançar exceção se existirem arquivos
                     // de tipos diferentes.

  if (input.areAssemblyFiles()) {
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
