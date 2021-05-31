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


TEST_CASE("should disable lines with BEGIN and END directives") {
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
  CHECK(assemblyData.getErrors().size() == 0);
  CHECK(      assemblyData.getNthSource(0).getLines()[0].isDisabled());
  CHECK_FALSE(assemblyData.getNthSource(0).getLines()[1].isDisabled());
  CHECK_FALSE(assemblyData.getNthSource(0).getLines()[2].isDisabled());
  CHECK(      assemblyData.getNthSource(0).getLines()[3].isDisabled());
}


TEST_CASE("should disable lines with PUBLIC directive") {
  AssemblyData assemblyData;
  assemblyData.addSource({{
    "my_module: begin",
    "random line",
    "public RANDOM_LABEL",
    "random line",
    "public RANDOM_LABEL2",
    "end"
  }});

  ZerothPass2 zerothPass2(&assemblyData);
  zerothPass2.run();

  auto source = assemblyData.getNthSource(0);

  INFO("source:");
  INFO(assemblyData.getNthSource(0));
  CHECK(assemblyData.getErrors().size() == 0);
  CHECK(      source.getLines()[0].isDisabled());
  CHECK_FALSE(source.getLines()[1].isDisabled());
  CHECK(      source.getLines()[2].isDisabled());
  CHECK_FALSE(source.getLines()[3].isDisabled());
  CHECK(      source.getLines()[4].isDisabled());
  CHECK(      source.getLines()[5].isDisabled());
}


TEST_CASE("should add labels to definitions table when using PUBLIC directive") {
  AssemblyData assemblyData;
  assemblyData.addSource({{
    "my_module: begin",
    "random line",
    "public MY_LABEL",
    "random line",
    "public RANDOM_LABEL",
    "end"
  }});

  ZerothPass2 zerothPass2(&assemblyData);
  zerothPass2.run();

  auto source = assemblyData.getNthSource(0);

  INFO("source:");
  INFO(assemblyData.getNthSource(0));
  CHECK(assemblyData.getErrors().size() == 0);
  CHECK(source.getDefinitionsTable().has("MY_LABEL"));
  CHECK(source.getDefinitionsTable().has("RANDOM_LABEL"));
}


TEST_CASE("should add error when using PUBLIC with missing symbol") {
  AssemblyData assemblyData;
  assemblyData.addSource({{
    "my_module: begin",
    "random line",
    "public ", // símbolo faltando
    "random line",
    "end"
  }});

  ZerothPass2 zerothPass2(&assemblyData);
  zerothPass2.run();

  AssemblyError expError(3, "missing symbol");

  REQUIRE(assemblyData.getErrors().size() == 1);
  auto gotError = assemblyData.getErrors().back();
  CHECK(expError == gotError);
}
