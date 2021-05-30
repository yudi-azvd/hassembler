#include <iostream>

#include "doctest/doctest.h"
#include "hasm/source.h"


TEST_CASE("source") {
  SourceContent originalContent = {{
    "one: const 1",
    "two: const 2"
  }};

  Source s = {
    originalContent
  };

  auto gotContent = s.getContent();

  CHECK_EQ(
    gotContent.getLines()[0].getContent(),
    originalContent.getLines()[0].getContent()
  );
  CHECK_EQ(
    gotContent.getLines()[1].getContent(),
    originalContent.getLines()[1].getContent()
  );
}
