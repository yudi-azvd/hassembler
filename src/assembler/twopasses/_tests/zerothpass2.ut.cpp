#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/twopasses/zerothpass2.h"
#include "assembler/assemblerdata.h"
#include "util/util.h"


TEST_CASE("should get module name") {
  AssemblerData* assemblerData = new AssemblerData();
  assemblerData->addSource({{
    "mod_a: begin",
    "end",
  }});

  ZerothPass2 zerothPass2(assemblerData);
  zerothPass2.run();

  CHECK("mod_a" == assemblerData->getNthSource(0).getModulename());
  delete assemblerData;
}


// TEST_CASE("should detect when module does not end") {
//   AssemblerData* assemblerData = new AssemblerData();
//   assemblerData->addSource({{
//     "mod_a: begin",
//   }});

//   ZerothPass2 zerothPass2(assemblerData);
//   zerothPass2.run();

//   CHECK("mod_a" == assemblerData->getNthSource(0).getModulename());
// }
