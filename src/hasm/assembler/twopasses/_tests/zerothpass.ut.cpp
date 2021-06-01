#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/twopasses/zerothpass.h"
#include "util/util.h"


TEST_SUITE_BEGIN("assembler-zerothpass");


/**
 * Não acho que vale muito à pena usar subcase
 * só pra usar setUp e tearDown
 */
TEST_CASE("ZerothPass") {
  AssemblyData* assemblyData = new AssemblyData();


  SUBCASE("should detect data section coming in first") {
    assemblyData->addSource({
      "section data",
      "section text",
    });

    ZerothPass zerothPass(assemblyData);
    zerothPass.run();

    CHECK_EQ(2, assemblyData->getNthSource(0)->getTextSectionLine());
    CHECK_EQ(1, assemblyData->getNthSource(0)->getDataSectionLine());
    CHECK(assemblyData->getNthSource(0)->dataSectionComesFirst());
  }


  SUBCASE("should detect data section coming in second") {
    assemblyData->addSource({
      "section text",
      "section data",
    });

    ZerothPass zerothPass(assemblyData);
    zerothPass.run();

    CHECK_EQ(1, assemblyData->getNthSource(0)->getTextSectionLine());
    CHECK_EQ(2, assemblyData->getNthSource(0)->getDataSectionLine());
    CHECK_FALSE(assemblyData->getNthSource(0)->dataSectionComesFirst());
  }


  SUBCASE("should detect sections with lines extra lines") {
    assemblyData->addSource({
      "section text",
      "output n1",
      "",
      "section data", // linha 4!
      "n1: const 3"
    });

    ZerothPass zerothPass(assemblyData);
    zerothPass.run();

    CHECK_EQ(1, assemblyData->getNthSource(0)->getTextSectionLine());
    CHECK_EQ(4, assemblyData->getNthSource(0)->getDataSectionLine());
    CHECK_FALSE(assemblyData->getNthSource(0)->dataSectionComesFirst());
  }

  delete assemblyData;
}


// Nenhum motivo especial além da preguiça:
TEST_CASE("should detect sections with lines extra lines - inverted") {
  AssemblyData* assemblyData = new AssemblyData();
  assemblyData->addSource({
    "section data",
    "n1: const 3",
    "section text", // linha 3!
    "",
    "output n1",
  });

  ZerothPass zerothPass(assemblyData);
  zerothPass.run();

  CHECK_EQ(3, assemblyData->getNthSource(0)->getTextSectionLine());
  CHECK_EQ(1, assemblyData->getNthSource(0)->getDataSectionLine());
  CHECK(assemblyData->getNthSource(0)->dataSectionComesFirst());
  delete assemblyData;
}


TEST_SUITE_END();
