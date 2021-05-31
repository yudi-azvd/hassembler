#include "hasmparametersparser.h"


HasmParametersParser::HasmParametersParser() {
  throw std::runtime_error("default constructor should not be used. Use "
  "'HasmParametersParser(std::vector<std::string> args)' instead");
}


HasmParametersParser::~HasmParametersParser() {}


HasmParametersParser::HasmParametersParser(std::vector<std::string> args) {
  arguments = args;
  arguments.shrink_to_fit();
}


HasmParameters HasmParametersParser::run() {
  checkForOuputFilenameFlag();
  checkForCompileOnlyFlag();
  getFileNames();
  throwIfOutputNameEqualsInputName();
  throwIfThereAreMultipleFilesAndOutputFlag();

  return assemblyParameters;
}


void HasmParametersParser::getFileNames() {
  if (arguments.size() == 0) {
    throw HasmParameterException("Não há arquivos de entrada");
  }

  assemblyParameters.filenames = arguments;
}


void HasmParametersParser::checkForCompileOnlyFlag() {
  std::vector<std::string>::iterator it =
    std::find(arguments.begin(), arguments.end(), COMPILE_ONLY_FLAG);

  bool flagNotFound = it == arguments.end();
  if (flagNotFound)
    return;

  assemblyParameters.isCompileOnly = true;
  arguments.erase(it);
}


void HasmParametersParser::checkForOuputFilenameFlag() {
  bool noSpaceForOutputName = false;
  std::vector<std::string>::iterator it
    = std::find(arguments.begin(), arguments.end(), OUTPUT_FILE_NAME_FLAG);

  bool flagNotFound = it == arguments.end();
  if (flagNotFound)
    return;

  noSpaceForOutputName = it + 1 > arguments.end() - 1;
  if (noSpaceForOutputName) {
    throw HasmParameterException("Falta o nome do arquivo depois de '-o'");
  }

  assemblyParameters.outputFilename = *(it + 1);
  arguments.erase(it, it + 2); // erase: [inicio, fim)
}


void HasmParametersParser::throwIfOutputNameEqualsInputName() {
  for (auto fileName : assemblyParameters.filenames) {
    if (fileName == assemblyParameters.outputFilename)
      throw HasmParameterException("Nome de saída é igual ao nome de entrada");
  }
}


void HasmParametersParser::throwIfThereAreMultipleFilesAndOutputFlag() {
  bool hasOutputFileName = !assemblyParameters.outputFilename.empty();
  bool hasMultipleInputFiles = assemblyParameters.filenames.size() > 1;
  if (hasMultipleInputFiles && hasOutputFileName) {
    throw HasmParameterException("Não é permitido usar '-o' com mútiplos arquivos");
  }
}
