#include "zerothpass2.h"


ZerothPass2::ZerothPass2() { }


ZerothPass2::ZerothPass2(AssemblyData* ad) : assemblyData{ad} { }


ZerothPass2::~ZerothPass2() {}


void ZerothPass2::run() {
  for (auto source : assemblyData->getSources()) {
    definitionsTable = source->getDefinitionsTable();
    usageTable = source->getUsageTable();
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

    try {
      tryToRunOnLine(line);
    }
    catch(const AssemblyError& e) {
      handleError(e);
    }

    lineCounter++;
  }

  try {
    checkForBeginAndEndMatch();
  }
  catch(const AssemblyError& e) {
    handleError(e);
  }
}


void ZerothPass2::tryToRunOnLine(Line line) {
  tokens = Scanner::parseTokens(line.getContent());
  lowerCasedTokens = stringVectorLowerCased(tokens);

  lineHasPublicDirective = findInVector(lowerCasedTokens, "public");
  lineHasBeginDirective = findInVector(lowerCasedTokens, "begin");
  lineHasEndDirective = findInVector(lowerCasedTokens, "end");
  lineHasExternDirective = findInVector(lowerCasedTokens, "extern");

  if (lineHasPublicDirective) {
    handlePublicDirective();
  }
  else if (lineHasBeginDirective) {
    handleBeginDirective();
  }
  else if(lineHasEndDirective) {
    handleEndDirective();
  }
  else if (lineHasExternDirective) {
    handleExternDirective();
  }
}


void ZerothPass2::handlePublicDirective() {
  source->disableLine(lineCounter);

  if (tokens.size() != 2) // essa linha deve ser PUBLIC [SYMBOL]
    throw AssemblyError(
      source->getInputfilename(),
      lineCounter,
      "missing symbol");

  definitionsTable->add(tokens[1], 0);
}


void ZerothPass2::handleBeginDirective() {
  source->setModulename(tokens[0]);
  source->disableLine(lineCounter);
}


void ZerothPass2::handleEndDirective() {
  sourceHasEndDirective = true;
  source->disableLine(lineCounter);
}


void ZerothPass2::handleExternDirective() {
  source->disableLine(lineCounter);

  if (tokens.size() != 3 || lowerCasedTokens[2] != "extern") {
    throw AssemblyError(
      source->getInputfilename(),
      lineCounter,
      "bad format using EXTERN directive. Use <LABEL>: EXTERN"
    );
  }

  if (tokens[1] != ":") {
    throw AssemblyError(
      source->getInputfilename(),
      lineCounter,
      "bad format using EXTERN directive. Missing ':'"
    );
  }

  usageTable->add(tokens[0], 0);
}


void ZerothPass2::checkForBeginAndEndMatch() {
  if (source->hasModule() && !sourceHasEndDirective) {
    throw AssemblyError(
      source->getInputfilename(),
      0,
      "module " + source->getModulename() +
      " does not end. Use the END directive"
    );
  }

  if (!source->hasModule() && sourceHasEndDirective) {
    throw AssemblyError(
      source->getInputfilename(),
      lineCounter-1, // última linha
      "module has not been defined but it has been ended");
  }
}


void ZerothPass2::handleError(const AssemblyError& e) {
  assemblyData->addError(e);
}
