#ifndef LINKER_H_INCLUDED
#define LINKER_H_INCLUDED

#include <iostream>

class Linker {
public:
  Linker(std::string str) {
    std::cout << "hello from linker" << str << std::endl;
  }

  ~Linker() {
    std::cout << "bye from linker" << std::endl;
  }
};

#endif // LINKER_H_INCLUDED