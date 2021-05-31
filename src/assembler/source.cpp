#include "source.h"


Source::Source(std::vector<const char*> lns)
  // : lines{lns}
{
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


std::vector<Line> Source::getLines() {
  return lines;
}


std::string Source::getLineContentAt(int index) {
  return lines[index].getContent();
}


