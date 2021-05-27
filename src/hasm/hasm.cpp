#include "hasm.h"


Hasm::Hasm() { }


Hasm::~Hasm() {
  delete assembler;
}


Hasm::Hasm(std::vector<std::string> args) {
  HasmParametersParser parser(args);
  parameters = parser.run();
  assembler = new Assembler(parameters.filenames);
}


void Hasm::run() {
  // inputFileGetter.run()
  // init assemblyData

  assembler->assemble();
  // if (!parameters.isCompileOnly) // refatorar pra .mustAlsoLink
  // linker = new Linker(assemblyData);
  // linker->link()

  // output assemblyData
  // outputGenerator.run()
}
