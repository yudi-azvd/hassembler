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
  checkForDumpHasmDataFlag();
  checkForOuputFilenameFlag();
  checkForCompileOnlyFlag();
  getFileNames();
  throwIfOutputNameEqualsInputName();
  throwIfThereAreMultipleFilesAndOutputFlag();

  return hasmParameters;
}


void HasmParametersParser::getFileNames() {
  if (arguments.size() == 0) {
    throw HasmParameterException("Não há arquivos de entrada");
  }

  hasmParameters.filenames = arguments;
}


void HasmParametersParser::checkForDumpHasmDataFlag() {
  auto it = std::find(arguments.begin(), arguments.end(), DUMP_HASM_DATA_FLAG);

  bool flagNotFound = it == arguments.end();
  if (flagNotFound)
    return;

  hasmParameters.dumpHasmData = true;
  arguments.erase(it);
}


void HasmParametersParser::checkForCompileOnlyFlag() {
  auto it = std::find(arguments.begin(), arguments.end(), COMPILE_ONLY_FLAG);

  bool flagNotFound = it == arguments.end();
  if (flagNotFound)
    return;

  hasmParameters.isCompileOnly = true;
  arguments.erase(it);
}


void HasmParametersParser::checkForOuputFilenameFlag() {
  bool noSpaceForOutputName = false;
  auto it = std::find(arguments.begin(), arguments.end(), OUTPUT_FILE_NAME_FLAG);

  bool flagNotFound = it == arguments.end();
  if (flagNotFound)
    return;

  noSpaceForOutputName = it + 1 > arguments.end() - 1;
  if (noSpaceForOutputName) {
    throw HasmParameterException("Falta o nome do arquivo depois de '-o'");
  }

  hasmParameters.outputFilename = *(it + 1);
  arguments.erase(it, it + 2); // erase: [inicio, fim)
}


void HasmParametersParser::throwIfOutputNameEqualsInputName() {
  for (auto fileName : hasmParameters.filenames) {
    if (fileName == hasmParameters.outputFilename)
      throw HasmParameterException("Nome de saída é igual ao nome de entrada");
  }
}


void HasmParametersParser::throwIfThereAreMultipleFilesAndOutputFlag() {
  bool hasOutputFileName = !hasmParameters.outputFilename.empty();
  bool hasMultipleInputFiles = hasmParameters.filenames.size() > 1;
  if (hasMultipleInputFiles && hasOutputFileName) {
    throw HasmParameterException("Não é permitido usar '-o' com mútiplos arquivos");
  }
}
