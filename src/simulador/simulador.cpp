#include <iostream>


class Simulator {

};


void showCorrectUsage();


int main(int commandlineCount, char* commandlineArguments[]) {
  if (commandlineCount <= 1) {
    showCorrectUsage();
    return 1;
  }

  // Simulator simulator(commandlineArguments[1]);

  // simulator.run();

  return 0;
}


void showCorrectUsage() {
  std::cout <<
    "Informe o nome do arquivo fonte a ser montado. Exemplo:\n" 
    "$ ./montador ./caminho/relativo/pro/seu/arquivo.asm" 
  << std::endl;
}

