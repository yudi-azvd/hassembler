#include "zerothpass.h"


ZerothPass::ZerothPass() { }


ZerothPass::ZerothPass(AssemblyData* ad) : assemblyData{ad} { }


ZerothPass::~ZerothPass() {}


void ZerothPass::run() {
  for (auto source : assemblyData->getSources()) {
    runOn(source);
  }
}


void ZerothPass::runOn(Source* source) {
  int lineCounter = 1;
  int dataSectionLine = 0, textSectionLine = 0;
  std::vector<std::string> tokens;

  for (auto& line : source->getLines()) {
    if (line.isDisabled()) {
      ++lineCounter;
      continue;
    }

    if (tokens.empty()) {
      ++lineCounter;
      continue;
    }

    tokens = Scanner::parseTokens(line.getContent());
    if (toLower(tokens[0]) != "section") {
      lineCounter++;
      continue;
    }

    if (toLower(tokens[1]) == "data") {
      dataSectionLine = lineCounter;
    }
    else if (toLower(tokens[1]) == "text") {
      textSectionLine = lineCounter;
    }
    else {
      // Devia dar um erro
    }

    if (dataSectionLine > 0 && textSectionLine > 0) {
      break;
    }

    lineCounter++;
  }

  source->setDataSectionLine(dataSectionLine);
  source->setTextSectionLine(textSectionLine);
  source->setDataSectionComesFirst(
    dataSectionLine < textSectionLine
  );
}
