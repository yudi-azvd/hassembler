#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/twopasses/zerothpass2.h"
#include "assembler/assemblerdata.h"
#include "util/util.h"


TEST_CASE("should get module name") {
  AssemblyData assemblyData;
  assemblyData.addSource({{
    "mod_a: begin",
    "end",
  }});

  ZerothPass2 zerothPass2(&assemblyData);
  zerothPass2.run();

  CHECK("mod_a" == assemblyData.getNthSource(0).getModulename());
}


TEST_CASE("should add error when module begins but does not end") {
  AssemblyData assemblyData;
  assemblyData.addSource({{
    "mod_a: begin",
    "random line",
    "random line",
  }});

  AssemblyError expError(0, "module mod_a does not end. Use the END directive");

  ZerothPass2 zerothPass2(&assemblyData);
  zerothPass2.run();

  REQUIRE(assemblyData.getErrors().size() == 1);
  auto gotError = assemblyData.getErrors().back();

  INFO("exp: ", expError);
  INFO("got: ", gotError);
  CHECK(expError == gotError);
}


TEST_CASE("should add error when module ends but does not begin") {
  AssemblyData assemblyData;
  assemblyData.addSource({{
    "random line",
    "random line",
    "end"
  }});

  AssemblyError expError(3, "module has not been defined but it has been ended");

  ZerothPass2 zerothPass2(&assemblyData);
  zerothPass2.run();

  REQUIRE(assemblyData.getErrors().size() == 1);
  auto gotError = assemblyData.getErrors().back();

  INFO("exp: ", expError);
  INFO("got: ", gotError);
  CHECK(expError == gotError);
}


TEST_CASE("should disable lines with begin and end directives") {
  AssemblyData assemblyData;
  assemblyData.addSource({{
    "my_module: begin",
    "random line",
    "random line",
    "end"
  }});

  ZerothPass2 zerothPass2(&assemblyData);
  zerothPass2.run();

  INFO("source:");
  INFO(assemblyData.getNthSource(0));
  CHECK(      assemblyData.getNthSource(0).getLines()[0].isDisabled());
  CHECK(      assemblyData.getNthSource(0).getLines()[3].isDisabled());
  CHECK_FALSE(assemblyData.getNthSource(0).getLines()[1].isDisabled());
  CHECK_FALSE(assemblyData.getNthSource(0).getLines()[2].isDisabled());
}
