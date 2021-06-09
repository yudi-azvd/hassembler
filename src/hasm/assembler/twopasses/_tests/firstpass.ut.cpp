#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/twopasses/firstpass.h"
#include "util/symbolstable.h"


TEST_SUITE_BEGIN("assembler-firstpass");


TEST_CASE("should get symbols in table") {
  SymbolsTable expectedTable;
  expectedTable.add("n1", 13);
  expectedTable.add("n2", 14);
  expectedTable.add("n3", 15);

  AssemblyData assemblyData;
  assemblyData.addSource({
    // "section text", // precisa aqui?
    "input n1",
    "input n2",
    "load n1",
    "add n2",
    "store n3",
    "output n3",
    "stop",
    // "section data", // precisa aqui?
    "n1: space ",
    "n2: space ",
    "n3: space  ",
  });

  FirstPass firstPass(&assemblyData);
  firstPass.run();

  // vai dar pau com alocação de memória?
  auto gotTable = assemblyData.getNthSource(0)->getSymbolsTable();

  CHECK(expectedTable == *gotTable);
}


TEST_SUITE_END();
