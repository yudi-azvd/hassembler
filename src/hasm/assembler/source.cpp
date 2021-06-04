#include "source.h"


Source::Source(std::vector<std::string> source, std::string filename) {
  inputFilename = filename;

  for (auto line : source) {
    lines.push_back(line);
  }
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


SymbolsTable* Source::getSymbolsTable() {
  return &symbolsTable;
}


std::ostream& operator<<(std::ostream& os, const Source& s) {
  int lineCounter = 1;
  char formattedLineCounter[5];

  if (!s.inputFilename.empty()) {
    std::string header = " FILENAME=" + s.inputFilename;
    os << header << std::endl;
    for(size_t i = 0; i < header.size()+1; ++i) os << "-";
    os << std::endl;
  }

  for (auto line : s.lines) {
    os << (line.isDisabled() ? "-" : " ");
    // Dificilmente uma arquivo .asm vai ter mais de 100 linhas
    std::sprintf(formattedLineCounter, "%2d", lineCounter);
    os << formattedLineCounter <<": ";
    os << line.getContent() << std::endl;
    ++lineCounter;
  }
  return os;
}
