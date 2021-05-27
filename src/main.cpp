#include <iostream>

#include "hasm/hasm.h"
#include "util/commandlineparser.h"


int main(int argc, const char* argv[]) {
  try {
    Hasm hasm(argc, argv);
    hasm.run();
  }
  catch(std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
