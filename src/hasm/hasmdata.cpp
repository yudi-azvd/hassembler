#include "hasmdata.h"

HasmData::HasmData(HasmParameters params) {
  outputFilename = params.outputFilename;
  _mustLink = !params.isCompileOnly;
}


HasmData::~HasmData() {}


bool HasmData::mustLink() {
  return _mustLink;
}
