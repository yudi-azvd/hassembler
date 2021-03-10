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

  std::string line, filename = commandlineArguments[1];
  std::vector<std::string> sourceFileContent;
  std::ifstream infile(filename);

  std::map<std::string, int> symbolTable;

  while (std::getline(infile, line)) {
    std::for_each(
      line.begin(), 
      line.end(), 
      [](char& c) { c = ::tolower(c); }
    );

    sourceFileContent.push_back(line);
  }

  Assembler assembler;

  sourceFileContent.shrink_to_fit();  

  assembler.assemble(sourceFileContent);

  // esse tipo de código não deveria estar dentro do assembler?
  std::vector<std::string> errors = assembler.errors();
  if (errors.size() > 0) {
    for (auto error : errors) {
      std::cout << error << std::endl;
    }
  }

  return 0;
}

void showCorrectUsage() {
  std::cout <<
    "Informe o nome do arquivo fonte a ser montado. Exemplo:\n" 
    "$ ./montador ./caminho/relativo/pro/seu/arquivo.asm" 
  << std::endl;
}
