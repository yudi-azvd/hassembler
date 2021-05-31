#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/twopasses/zerothpass.h"
#include "util/util.h"


/**
 * Não acho que vale muito à pena usar subcase
 * só pra usar setUp e tearDown
 */
TEST_CASE("ZerothPass") {
  AssemblerData* assemblerData = new AssemblerData();


  SUBCASE("should detect data section coming in first") {
    assemblerData->addSource({{
      "section data",
      "section text",
    }});

    ZerothPass zerothPass(assemblerData);
    zerothPass.run();

    CHECK_EQ(2, assemblerData->getNthSource(0).getTextSectionLine());
    CHECK_EQ(1, assemblerData->getNthSource(0).getDataSectionLine());
    CHECK(assemblerData->getNthSource(0).dataSectionComesFirst());
  }


  SUBCASE("should detect data section coming in second") {
    assemblerData->addSource({{
      "section text",
      "section data",
    }});

    ZerothPass zerothPass(assemblerData);
    zerothPass.run();

    CHECK_EQ(1, assemblerData->getNthSource(0).getTextSectionLine());
    CHECK_EQ(2, assemblerData->getNthSource(0).getDataSectionLine());
    CHECK_FALSE(assemblerData->getNthSource(0).dataSectionComesFirst());
  }


  SUBCASE("should detect sections with lines extra lines") {
    assemblerData->addSource({{
      "section text",
      "output n1",
      "",
      "section data", // linha 4!
      "n1: const 3"
    }});

    ZerothPass zerothPass(assemblerData);
    zerothPass.run();

    CHECK_EQ(1, assemblerData->getNthSource(0).getTextSectionLine());
    CHECK_EQ(4, assemblerData->getNthSource(0).getDataSectionLine());
    CHECK_FALSE(assemblerData->getNthSource(0).dataSectionComesFirst());
  }

  delete assemblerData;
}


// Nenhum motivo especial além da preguiça:
TEST_CASE("should detect sections with lines extra lines - inverted") {
  AssemblerData* assemblerData = new AssemblerData();
  assemblerData->addSource({{
    "section data",
    "n1: const 3",
    "section text", // linha 3!
    "",
    "output n1",
  }});

  ZerothPass zerothPass(assemblerData);
  zerothPass.run();

  CHECK_EQ(3, assemblerData->getNthSource(0).getTextSectionLine());
  CHECK_EQ(1, assemblerData->getNthSource(0).getDataSectionLine());
  CHECK(assemblerData->getNthSource(0).dataSectionComesFirst());
  delete assemblerData;
}
