#include "hasmdata.h"

HasmData::HasmData(HasmParameters params) {
  outputFilename = params.outputFilename;
  _mustLink = !params.isCompileOnly;
}


HasmData::~HasmData() {}


AssemblyData* HasmData::getAssemblyData() {
  return assemblyData;
}


std::vector<std::string> HasmData::getFilenames() {
  return assemblyData->getInputFilenames();
}


void HasmData::addSource(std::vector<std::string> source) {
  assemblyData->addSource(source);
}


bool HasmData::mustLink() {
  return _mustLink;
}
