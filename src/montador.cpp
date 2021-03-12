#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>

#include "../include/assembler.h"


void showCorrectUsage();


int main(int commandlineCount, char* commandlineArguments[]) {
  if (commandlineCount <= 1) {
    showCorrectUsage();
    return 1;
  }

  // std::string line, filename = commandlineArguments[1];
  // std::vector<std::string> sourceFileContent;
  // std::fstream infile(filename);

  // std::map<std::string, int> symbolTable;

  // while (std::getline(infile, line)) {
  //   sourceFileContent.push_back(line);
  // }

  Assembler assembler;

  assembler.getInputFileContent(commandlineArguments[1]);

  // sourceFileContent.shrink_to_fit();  

  // assembler.assemble(sourceFileContent);
  assembler.assemble();

  return 0;
}


void showCorrectUsage() {
  std::cout <<
    "Informe o nome do arquivo fonte a ser montado. Exemplo:\n" 
    "$ ./montador ./caminho/relativo/pro/seu/arquivo.asm" 
  << std::endl;
}
