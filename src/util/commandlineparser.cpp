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


// Melhor funções menores que pegam cada interesse: arquivo de entrada,
// arquivo de saída, etc
AssemblyOptions CommandLineParser::run() {
  checkForOuputFileNameFlag();
  checkForCompileOnlyFlag();
  getFileNames();
  checkForMultipleFilesAndOutputFlag();
  
  return assemblyOptions;
}


void CommandLineParser::getFileNames() {
  std::string arg;
  for (size_t i = 0; i < arguments.size(); ++i) {
    arg = arguments[i];
    assemblyOptions.fileNames.push_back(arg);
  }

  if (assemblyOptions.fileNames.size() == 0) {
    throw std::invalid_argument("Não há arquivos de entrada");
  }

  assemblyOptions.fileNames.shrink_to_fit();
}


void CommandLineParser::checkForCompileOnlyFlag() {
  std::vector<std::string>::iterator flagPosition;

  for (size_t i = 0; i < arguments.size(); ++i) {
    if (arguments[i] != COMPILE_ONLY_FLAG)
      continue;
    
    flagPosition = arguments.begin() + i;
    assemblyOptions.isCompileOnly = true;
    break;
  }
  
  if (assemblyOptions.isCompileOnly)
    arguments.erase(flagPosition);
}


void CommandLineParser::checkForOuputFileNameFlag() {
  int size = arguments.size();
  bool noSpaceForOutputName = false;
  std::vector<std::string>::iterator flagPosition;
  std::string arg;
  
  for (int i = 0; i < size; ++i) {
    arg = arguments[i];
    if (arg != OUTPUT_FILE_NAME_FLAG) {
      continue;
    }

    noSpaceForOutputName = i + 1 > size - 1;
    if (noSpaceForOutputName) {
      throw std::invalid_argument("Falta o nome do arquivo depois de '-o'");
    }

    flagPosition = arguments.begin() + i;
    assemblyOptions.outputFileName = arguments[i+1];
    break;
  }

  if (!assemblyOptions.outputFileName.empty())
    arguments.erase(flagPosition, flagPosition+2);
}




void CommandLineParser::checkForMultipleFilesAndOutputFlag() {
  bool hasOutputFileName = !assemblyOptions.outputFileName.empty();
  bool hasMultipleInputFiles = assemblyOptions.fileNames.size() > 1;
  if (hasMultipleInputFiles && hasOutputFileName) {
    throw std::invalid_argument("Não é permitido usar '-o' com mútiplos arquivos");
  }
}
