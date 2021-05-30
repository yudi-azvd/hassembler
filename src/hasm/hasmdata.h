#ifndef HASMDATA_H_INCLUDED
#define HASMDATA_H_INCLUDED

#include <iostream>
#include <vector>

#include "hasmparameters.h"
#include "source.h"

#include "util/correctionfactortable.hpp"


class HasmData {
public:
  HasmData(HasmParameters params);

  ~HasmData();

  bool mustLink();

private:
  std::vector<Source> sources;

  std::string outputFilename;

  bool _mustLink;
};


#endif // HASMDATA_H_INCLUDED
