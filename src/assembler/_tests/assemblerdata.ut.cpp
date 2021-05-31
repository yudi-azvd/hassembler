#include <iostream>

#include "doctest/doctest.h"
#include "assembler/assemblerdata.h"


TEST_CASE("assembler data") {
  AssemblerData* assemblerData = new AssemblerData();
  assemblerData->addSource({{
    "one line",
    "two lines",
  }});

  std::vector<Source*> gotSources = assemblerData->getSources();

  CHECK("one line"  == gotSources[0]->getLineContentAt(0));
  CHECK("two lines" == gotSources[0]->getLineContentAt(1));
  delete assemblerData;
}
