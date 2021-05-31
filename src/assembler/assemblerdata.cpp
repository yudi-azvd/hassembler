#include "assemblerdata.h"


AssemblyData::AssemblyData() {}


AssemblyData::~AssemblyData() {
  for (auto s : sources) delete s;
}


void AssemblyData::addSource(std::vector<const char*> source) {
  Source* s = new Source(source);
  sources.push_back(s);
}


size_t AssemblyData::getSourcesSize() {
  return sources.size();
}


std::vector<Source*> AssemblyData::getSources() {
  return sources;
}


Source AssemblyData::getNthSource(int index) {
  return *sources[index];
}


void AssemblyData::addError(std::string filename, int line, std::string message) {
  AssemblyError e(filename, line, message);
  errors.push_back(e);
}


std::vector<AssemblyError> AssemblyData::getErrors() {
  return errors;
}
