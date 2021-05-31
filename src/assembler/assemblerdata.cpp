#include "assemblerdata.h"


AssemblerData::AssemblerData() {}


AssemblerData::~AssemblerData() {
  for (auto s : sources) delete s;
}


void AssemblerData::addSource(std::vector<const char*> source) {
  Source* s = new Source(source);
  sources.push_back(s);
}


size_t AssemblerData::getSourcesSize() {
  return sources.size();
}


std::vector<Source*> AssemblerData::getSources() {
  return sources;
}


Source AssemblerData::getNthSource(int index) {
  return *sources[index];
}

