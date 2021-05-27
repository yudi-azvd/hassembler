#include "hasm.h"


Hasm::Hasm() { }


Hasm::~Hasm() {
  delete assembler;
}


Hasm::Hasm(int argc, const char** argv) {
  HasmParametersParser parser(argc, argv);
  parameters = parser.run();
  assembler = new Assembler(parameters.fileNames);
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
