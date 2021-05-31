#include "source.h"


Source::Source(std::vector<const char*> lns) {
  std::vector<Line> tmp(lns.begin(), lns.end());
  lines = tmp;
}


Source::~Source() {}


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


void Source::setModulename(std::string name) {
  modulename = name;
}


std::string Source::getModulename() {
  return modulename;
}


bool Source::hasModule() {
  return !modulename.empty();
}


std::string Source::getInputfilename() {
  return inputFilename;
}


std::vector<Line> Source::getLines() {
  return lines;
}


void Source::disableLine(int line) {
  lines[line-1].disable();
}


std::string Source::getLineContentAt(int index) {
  return lines[index].getContent();
}


DefinitionsTable* Source::getDefinitionsTable() {
  return &definitionsTable;
}


UsageTable* Source::getUsageTable() {
  return &usageTable;
}


std::ostream& operator<<(std::ostream& os, const Source& s) {
  int lineCounter = 1;
  os << s.inputFilename << std::endl;
  for (auto line : s.lines) {
    os << (line.isDisabled() ? "-" : "+");
    os << lineCounter <<": ";
    os << line.getContent() << std::endl;
    ++lineCounter;
  }
  return os;
}

