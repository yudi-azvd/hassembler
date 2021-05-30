#include "source.h"


Source::Source(SourceContent& content)
  : sourceContent{content}
{}


Source::Source(std::vector<const char*> lines)
  : sourceContent{lines}
{}


Source::~Source() {}


SourceContent& Source::getContent() {
  return sourceContent;
}


void Source::setDataSectionComesFirst(bool comesFirst) {
  _dataSectionComesFirst = comesFirst;
}


bool Source::dataSectionComesFirst() {
  return _dataSectionComesFirst;
}


int Source::getDataSectionLine() {
  return dataSectionLine;
}


void Source::setDataSectionLine(int line) {
  dataSectionLine = line;
}


int Source::getTextSectionLine() {
  return textSectionLine;
}


void Source::setTextSectionLine(int line) {
  textSectionLine = line;
}
