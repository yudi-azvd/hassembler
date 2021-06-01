#include "hasmparametersparser.h"


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
    throw HasmParameterException("no input files");
  }

  hasmParameters.filenames = arguments;
}


void HasmParametersParser::checkForDumpHasmDataFlag() {
  find(DUMP_HASM_DATA_FLAG);

  if (flagNotFound())
    return;

  hasmParameters.dumpHasmData = true;
  arguments.erase(iter);
}


void HasmParametersParser::checkForCompileOnlyFlag() {
  find(COMPILE_ONLY_FLAG);

  if (flagNotFound())
    return;

  hasmParameters.isCompileOnly = true;
  arguments.erase(iter);
}


void HasmParametersParser::checkForOuputFilenameFlag() {
  find(OUTPUT_FILE_NAME_FLAG);

  if (flagNotFound())
    return;

  bool noSpaceForOutputName = false;
  noSpaceForOutputName = iter + 1 > arguments.end() - 1;
  if (noSpaceForOutputName) {
    throw HasmParameterException("missing file name after '-o'");
  }

  hasmParameters.outputFilename = *(iter + 1);
  arguments.erase(iter, iter + 2); // erase: [inicio, fim)
}


void HasmParametersParser::find(const std::string flag) {
  iter = std::find(arguments.begin(), arguments.end(), flag);
}


bool HasmParametersParser::flagNotFound() {
  return iter == arguments.end();
}


void HasmParametersParser::throwIfOutputNameEqualsInputName() {
  for (auto fileName : hasmParameters.filenames) {
    if (fileName == hasmParameters.outputFilename)
      throw HasmParameterException("output name is same as input name");
  }
}


void HasmParametersParser::throwIfThereAreMultipleFilesAndOutputFlag() {
  bool hasOutputFileName = !hasmParameters.outputFilename.empty();
  bool hasMultipleInputFiles = hasmParameters.filenames.size() > 1;
  if (hasMultipleInputFiles && hasOutputFileName) {
    throw HasmParameterException("not allowed to use '-o' with multiple input files");
  }
}
