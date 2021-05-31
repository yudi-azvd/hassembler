#include <iostream>

#include "doctest/doctest.h"
#include "assembler/assemblerdata.h"


TEST_CASE("assembler data") {
  AssemblyData* assemblyData = new AssemblyData();
  assemblyData->addSource({{
    "one line",
    "two lines",
  }});

  std::vector<Source*> gotSources = assemblyData->getSources();

  CHECK("one line"  == gotSources[0]->getLineContentAt(0));
  CHECK("two lines" == gotSources[0]->getLineContentAt(1));
  delete assemblyData;
}
