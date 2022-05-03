#include <iostream>

#include "doctest.h"
#include "assembler/source.h"


TEST_SUITE_BEGIN("assembler-source");


TEST_CASE("normal source") {
  Source s = {{
    "one: const 1",
    "two: const 2"
  }};

  auto gotLines = s.getLines();

  CHECK_EQ(
    "one: const 1",
    gotLines[0].getContent()
  );
  CHECK_EQ(
    "two: const 2",
    gotLines[1].getContent()
  );
}


TEST_CASE("pointer to source") {
  Source* source = new Source({
      "n1: space",
      "n2: const 2",
  });

  CHECK(source->getLineContentAt(0) == "n1: space");
  CHECK(source->getLineContentAt(1) == "n2: const 2");
  delete source;
}


TEST_CASE("vector of sources") {
  std::vector<Source> sources = { // vector
    { // Source
      { // vector
        "one", // Line
        "two", // Line
      }
    }
  };

  CHECK("one" == sources[0].getLines()[0].getContent());
}


TEST_CASE("vector of pointers to source") {
  Source source1 = {{
    "n1: space",
    "n2: const 2"}};
  Source source2 = {{
    "n3: space",
    "n4: const 4"}};

  std::vector<Source*> sourcesPtrVector = {{
    &source1,
    &source2
  }};

  CHECK("n1: space"   == sourcesPtrVector[0]->getLineContentAt(0));
  CHECK("n2: const 2" == sourcesPtrVector[0]->getLineContentAt(1));
  CHECK("n3: space"   == sourcesPtrVector[1]->getLineContentAt(0));
  CHECK("n4: const 4" == sourcesPtrVector[1]->getLineContentAt(1));
}


TEST_SUITE_END();
