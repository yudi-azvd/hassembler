#include "zerothpass.h"


ZerothPass::ZerothPass(Source& s) : source{s} { }


ZerothPass::~ZerothPass() {}


void ZerothPass::run() {
  int lineCounter = 1;
  int dataSectionLine = 0, textSectionLine = 0;
  std::vector<std::string> tokens;

  auto sourceContent = source.getContent();
  for (auto& line : sourceContent.getLines()) {
    tokens = Scanner::parseTokens(line.getContent());

    if (tokens.empty()) {
      lineCounter++;
      continue;
    }

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

    if (dataSectionLine > 0 && textSectionLine > 0) {
      break;
    }

    lineCounter++;
  }

  source.setDataSectionLine(dataSectionLine);
  source.setTextSectionLine(textSectionLine);
  source.setDataSectionComesFirst(
    dataSectionLine < textSectionLine
  );
}
