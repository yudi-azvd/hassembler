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


AssemblyOptions CommandLineParser::run() {
  checkForOuputFileNameFlag();
  checkForCompileOnlyFlag();
  getFileNames();
  throwIfOutputNameEqualsInputName();
  checkForMultipleFilesAndOutputFlag();
  
  return assemblyOptions;
}


void CommandLineParser::getFileNames() {
  if (arguments.size() == 0) {
    throw std::invalid_argument("Não há arquivos de entrada");
  }

  assemblyOptions.fileNames = arguments;
}


void CommandLineParser::checkForCompileOnlyFlag() {
  size_t i;
  std::vector<std::string>::iterator flagPosition;

  for (i = 0; i < arguments.size(); ++i)
    if (arguments[i] == COMPILE_ONLY_FLAG)
      break;

  bool flagFound = i < arguments.size();
  if (!flagFound) 
    return;

  flagPosition = arguments.begin() + i;
  assemblyOptions.isCompileOnly = true;
  
  if (flagFound)
    arguments.erase(flagPosition);
}


void CommandLineParser::checkForOuputFileNameFlag() {
  int i, size = arguments.size();
  bool noSpaceForOutputName = false;
  std::vector<std::string>::iterator flagPosition;
  std::string arg;
  
  for (i = 0; i < size; ++i)
    if (arguments[i] == OUTPUT_FILE_NAME_FLAG)
      break;
  
  bool flagFound = i < size;
  if (!flagFound)
    return;

  noSpaceForOutputName = i + 1 > size - 1;
  if (noSpaceForOutputName) {
    throw std::invalid_argument("Falta o nome do arquivo depois de '-o'");
  }

  flagPosition = arguments.begin() + i;
  assemblyOptions.outputFileName = arguments[i+1];

  if (flagFound)
    arguments.erase(flagPosition, flagPosition+2);
}


void CommandLineParser::throwIfOutputNameEqualsInputName() {
  for (auto fileName : assemblyOptions.fileNames) {
    if (fileName == assemblyOptions.outputFileName)
      throw std::invalid_argument("Nome de saída é igual ao nome de entrada");
  }
}


void CommandLineParser::checkForMultipleFilesAndOutputFlag() {
  bool hasOutputFileName = !assemblyOptions.outputFileName.empty();
  bool hasMultipleInputFiles = assemblyOptions.fileNames.size() > 1;
  if (hasMultipleInputFiles && hasOutputFileName) {
    throw std::invalid_argument("Não é permitido usar '-o' com mútiplos arquivos");
  }
}
