#ifndef HASMPARAMETERSPARSER_H_INCLUDED
#define HASMPARAMETERSPARSER_H_INCLUDED

#include <iostream>
#include <exception>
#include <algorithm>

#include "hasmparameters.h"
#include "hasmparameterexception.h"


class HasmParametersParser {
public:
  HasmParametersParser(std::vector<std::string> args);

  ~HasmParametersParser();

  HasmParameters run();

private:
  const std::string OUTPUT_FILE_NAME_FLAG = "-o";

  const std::string COMPILE_ONLY_FLAG = "-c";

  const std::string DUMP_HASM_DATA_FLAG = "-dh";

  std::vector<std::string> arguments;

  std::vector<std::string>::iterator iter;

  HasmParameters hasmParameters;

  bool hasMultipleInputFiles();

  void checkForDumpHasmDataFlag();

  void checkForOuputFilenameFlag();

  void checkForCompileOnlyFlag();

  void find(const std::string flag);

  bool flagNotFound();

  void getFileNames();

  void throwIfThereAreMultipleFilesAndOutputFlag();

  void throwIfOutputNameEqualsInputName();
};

#endif // HASMPARAMETERSPARSER_H_INCLUDED
