#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/twopasses/zerothpass.h"
#include "util/util.h"


TEST_SUITE_BEGIN("assembler-zerothpass");


TEST_CASE("should detect data section coming in first") {
  AssemblyData assemblyData;
  assemblyData.addSource({
    "section data",
    "section text",
  });

  ZerothPass zerothPass(&assemblyData);
  zerothPass.run();

  CHECK_EQ(2, assemblyData.getNthSource(0)->getTextSectionLine());
  CHECK_EQ(1, assemblyData.getNthSource(0)->getDataSectionLine());
  CHECK(assemblyData.getNthSource(0)->dataSectionComesFirst());
}


TEST_CASE("should detect data section coming in second") {
  AssemblyData assemblyData;
  assemblyData.addSource({
    "section text",
    "section data",
  });

  ZerothPass zerothPass(&assemblyData);
  zerothPass.run();

  CHECK_EQ(1, assemblyData.getNthSource(0)->getTextSectionLine());
  CHECK_EQ(2, assemblyData.getNthSource(0)->getDataSectionLine());
  CHECK_FALSE(assemblyData.getNthSource(0)->dataSectionComesFirst());
}


TEST_CASE("should detect sections with lines extra lines") {
  AssemblyData assemblyData;
  assemblyData.addSource({
    "section text",
    "output n1",
    "",
    "section data", // linha 4!
    "n1: const 3"
  });

  ZerothPass zerothPass(&assemblyData);
  zerothPass.run();

  CHECK_EQ(1, assemblyData.getNthSource(0)->getTextSectionLine());
  CHECK_EQ(4, assemblyData.getNthSource(0)->getDataSectionLine());
  CHECK_FALSE(assemblyData.getNthSource(0)->dataSectionComesFirst());
}


TEST_CASE("should detect sections with lines extra lines - inverted") {
  AssemblyData assemblyData;
  assemblyData.addSource({
    "section data",
    "n1: const 3",
    "section text", // linha 3!
    "",
    "output n1",
  });

  ZerothPass zerothPass(&assemblyData);
  zerothPass.run();

  CHECK_EQ(3, assemblyData.getNthSource(0)->getTextSectionLine());
  CHECK_EQ(1, assemblyData.getNthSource(0)->getDataSectionLine());
  CHECK(assemblyData.getNthSource(0)->dataSectionComesFirst());
}


TEST_SUITE_END();
