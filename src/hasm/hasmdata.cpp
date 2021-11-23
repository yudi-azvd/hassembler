#include "hasmdata.h"


HasmData::HasmData(HasmParameters params) {
  assemblyData = new AssemblyData();
  //linkageData = new LinkageData();
  inputFilenames = params.filenames;
  outputFilename = params.outputFilename;
  _mustLink = !params.isCompileOnly;
}


HasmData::~HasmData() {
  delete assemblyData;
}


AssemblyData* HasmData::getAssemblyData() {
  return assemblyData;
}


std::vector<std::string> HasmData::getFilenames() {
  return inputFilenames;
}


void HasmData::addSource(std::vector<std::string> source, std::string filename) {
  assemblyData->addSource(source, filename);
}


bool HasmData::mustLink() {
  return _mustLink;
}
