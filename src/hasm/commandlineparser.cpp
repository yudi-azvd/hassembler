#include "commandlineparser.h"

CommandLineParser::CommandLineParser() {
  throw std::invalid_argument("default constructor should not be used. Use "
  "'CommandLineParser(int argc, const char* argv[])' instead");
}


CommandLineParser::~CommandLineParser() {}


CommandLineParser::CommandLineParser(int argc, const char* argv[]) {
  constexpr int executableNameOffset = 1;
  std::vector<std::string> v(argv+executableNameOffset, argv + argc);
  arguments = v;
  arguments.shrink_to_fit();
}


HasmParameters CommandLineParser::run() {
  checkForOuputFileNameFlag();
  checkForCompileOnlyFlag();
  getFileNames();
  throwIfOutputNameEqualsInputName();
  throwIfThereAreMultipleFilesAndOutputFlag();

  return assemblyParameters;
}


void CommandLineParser::getFileNames() {
  if (arguments.size() == 0) {
    throw std::invalid_argument("Não há arquivos de entrada");
  }

  assemblyParameters.fileNames = arguments;
}


void CommandLineParser::checkForCompileOnlyFlag() {
  size_t i;
  std::vector<std::string>::iterator it =
    std::find(arguments.begin(), arguments.end(), COMPILE_ONLY_FLAG);

  bool flagNotFound = it == arguments.end();
  if (flagNotFound)
    return;

  assemblyParameters.isCompileOnly = true;
  arguments.erase(it);
}


void CommandLineParser::checkForOuputFileNameFlag() {
  int i, size = arguments.size();
  bool noSpaceForOutputName = false;
  std::vector<std::string>::iterator it
    = std::find(arguments.begin(), arguments.end(), OUTPUT_FILE_NAME_FLAG);

  bool flagNotFound = it == arguments.end();
  if (flagNotFound)
    return;

  noSpaceForOutputName = it + 1 > arguments.end() - 1;
  if (noSpaceForOutputName) {
    throw std::invalid_argument("Falta o nome do arquivo depois de '-o'");
  }

  assemblyParameters.outputFileName = *(it + 1);
  arguments.erase(it, it + 2); // erase: [inicio, fim)
}


void CommandLineParser::throwIfOutputNameEqualsInputName() {
  for (auto fileName : assemblyParameters.fileNames) {
    if (fileName == assemblyParameters.outputFileName)
      throw std::invalid_argument("Nome de saída é igual ao nome de entrada");
  }
}


void CommandLineParser::throwIfThereAreMultipleFilesAndOutputFlag() {
  bool hasOutputFileName = !assemblyParameters.outputFileName.empty();
  bool hasMultipleInputFiles = assemblyParameters.fileNames.size() > 1;
  if (hasMultipleInputFiles && hasOutputFileName) {
    throw std::invalid_argument("Não é permitido usar '-o' com mútiplos arquivos");
  }
}
