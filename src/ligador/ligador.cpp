#include <iostream>
#include <vector>

#include "linker.hpp"


void showCorrectUsage();


int main(int commandlineCount, char* commandlineArguments[]) {
  std::vector<std::string> filenames;

  bool correctCommandlineArgumentsCount = 
    1 <= commandlineCount && commandlineCount <= 4;
  if (!correctCommandlineArgumentsCount) {
    showCorrectUsage();
    return 1;
  }

  for (int i = 1; i < commandlineCount; i++) {
    filenames.push_back(commandlineArguments[i]);
  }

  Linker linker(filenames);

  linker.link();

  return 0;
}


void showCorrectUsage() {
  std::cout <<
    "Informe os nomes dos arquivos objeto a serem ligados. Exemplo:\n" 
    "$ ./ligador arq1.obj arq2.obj arq2.obj" 
  << std::endl;
}
