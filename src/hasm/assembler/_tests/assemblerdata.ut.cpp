#include <iostream>

#include "doctest.h"
#include "assembler/assemblydata.h"


TEST_SUITE_BEGIN("assembler-assemblydata");


TEST_CASE("assembler data - const char*") {
  AssemblyData* assemblyData = new AssemblyData();
  assemblyData->addSource({
    "one line",
    "two lines",
  });

  std::vector<Source*> gotSources = assemblyData->getSources();

  CHECK("one line"  == gotSources[0]->getLineContentAt(0));
  CHECK("two lines" == gotSources[0]->getLineContentAt(1));
  delete assemblyData;
}


TEST_CASE("assembler data - strings") {
  AssemblyData* assemblyData = new AssemblyData();
  std::vector<std::string> firstSource = {
    "one line",
    "two lines",
  };

  assemblyData->addSource(firstSource);

  std::vector<Source*> gotSources = assemblyData->getSources();

  CHECK("one line"  == gotSources[0]->getLineContentAt(0));
  CHECK("two lines" == gotSources[0]->getLineContentAt(1));
  delete assemblyData;
}


TEST_SUITE_END();
