#include "zerothpass2.h"


ZerothPass2::ZerothPass2(AssemblerData* ad) : assemblerData{ad} { }


ZerothPass2::~ZerothPass2() {}


void ZerothPass2::run() {
  for (auto source : assemblerData->getSources()) {
    runOn(source);
  }
}


void ZerothPass2::runOn(Source* source) {
  int lineCounter = 1;
  bool lineHasBegin;
  std::vector<std::string> tokens, lowerCasedTokens;

  for (auto line : source->getLines()) {
    if (line.isDisabled()) {
      ++lineCounter;
      continue;
    }

    tokens = Scanner::parseTokens(line.getContent());
    lowerCasedTokens = stringVectorLowerCased(tokens);

    lineHasBegin = findInVector(lowerCasedTokens, "begin");
    if (lineHasBegin) {
      source->setModulename(tokens[0]);
    }
  }
}
