#include <iostream>

#include "hasm/hasm.h"


int main(int argc, const char* argv[]) {
  const int executableNameOffset = 1;
  std::vector<std::string> args(argv+executableNameOffset, argv + argc);

  try {
    Hasm hasm(args);
    hasm.run();
  }
  catch(HasmParameterException& e) {
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  catch(...) {
    std::cout << "Algo de errado não deu certo..." << std::endl;
    return EXIT_FAILURE;
  }

  return 0;
}
