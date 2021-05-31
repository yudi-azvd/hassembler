#include "zerothpass2.h"


ZerothPass2::ZerothPass2(AssemblyData* ad) : assemblyData{ad} { }


ZerothPass2::~ZerothPass2() {}


void ZerothPass2::run() {
  for (auto source : assemblyData->getSources()) {
    runOn(source);
  }
}


void ZerothPass2::runOn(Source* source) {
  int lineCounter = 1;
  bool lineHasBeginDirective, lineHasEndDirective,
    sourceHasEndDirective = false;
  std::vector<std::string> tokens, lowerCasedTokens;

  for (auto line : source->getLines()) {
    if (line.isDisabled()) {
      ++lineCounter;
      continue;
    }

    tokens = Scanner::parseTokens(line.getContent());
    lowerCasedTokens = stringVectorLowerCased(tokens);

    lineHasBeginDirective = findInVector(lowerCasedTokens, "begin");
    lineHasEndDirective = findInVector(lowerCasedTokens, "end");

    if (lineHasBeginDirective) {
      source->setModulename(tokens[0]);
      source->disableLine(lineCounter);
    }
    else if(lineHasEndDirective) {
      sourceHasEndDirective = true;
      source->disableLine(lineCounter);
    }

    lineCounter++;
  }

  if (source->hasModule() && !sourceHasEndDirective) {
    assemblyData->addError(
      source->getInputfilename(),
      0,
      "module " + source->getModulename() + " does not end. Use the END directive");
  }

  if (!source->hasModule() && sourceHasEndDirective) {
    assemblyData->addError(
      source->getInputfilename(),
      lineCounter-1, // última linha
      "module has not been defined but it has been ended");
  }
}
