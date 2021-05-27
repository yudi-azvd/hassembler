#include <iostream>

#include "hasm/hasm.h"


int main(int argc, const char* argv[]) {
  const int executableNameOffset = 1;
  std::vector<std::string> args(argv+executableNameOffset, argv + argc);

  try {
    Hasm hasm(args);
    hasm.run();
  }
  catch(std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
