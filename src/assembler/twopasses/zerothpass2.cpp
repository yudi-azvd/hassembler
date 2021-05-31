#include "zerothpass2.h"


ZerothPass2::ZerothPass2(AssemblyData* ad) : assemblyData{ad} { }


ZerothPass2::~ZerothPass2() {}


void ZerothPass2::run() {
  for (auto source : assemblyData->getSources()) {
    runOn(source);
  }
}


void ZerothPass2::runOn(Source* src) {
  lineCounter = 1;
  source = src;

  for (auto line : source->getLines()) {
    if (line.isDisabled()) {
      ++lineCounter;
      continue;
    }

    tokens = Scanner::parseTokens(line.getContent());
    lowerCasedTokens = stringVectorLowerCased(tokens);

    lineHasPublicDirective = findInVector(lowerCasedTokens, "public");
    lineHasBeginDirective = findInVector(lowerCasedTokens, "begin");
    lineHasEndDirective = findInVector(lowerCasedTokens, "end");

    if (lineHasPublicDirective) {
      handlePublicDirective();
    }
    else if (lineHasBeginDirective) {
      handleBeginDirective();
    }
    else if(lineHasEndDirective) {
      handleEndDirective();
    }

    lineCounter++;
  }

  checkForBeginAndEndMatch();
}


void ZerothPass2::handlePublicDirective() {
  source->disableLine(lineCounter);
  if (tokens.size() != 2) {  // essa linha deve ser PUBLIC [SYMBOL]
    assemblyData->addError(
      source->getInputfilename(),
      lineCounter,
      "missing symbol");
  }
  else {
    source->addToDefinitionsTable(tokens[1], 0);
  }
}


void ZerothPass2::handleBeginDirective() {
  source->setModulename(tokens[0]);
  source->disableLine(lineCounter);
}


void ZerothPass2::handleEndDirective() {
  sourceHasEndDirective = true;
  source->disableLine(lineCounter);
}


void ZerothPass2::checkForBeginAndEndMatch() {
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
