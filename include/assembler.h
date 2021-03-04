#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include <iostream>
#include <map>

struct LineAndItsTokens {
  std::string line;
  std::vector<std::string> tokens;

  friend std::ostream &operator<<(std::ostream& os, const LineAndItsTokens& line);
};


class Assembler {
private:

  std::map<std::string, int> symbolTable;
  
  std::map<std::string, int> opcodeTable;

  std::vector<std::string> sourceFileContent;


public:
  Assembler();

  ~Assembler();

  void assemble(std::vector<std::string> sourceFileContent);
  
  void runFirstPass();

  std::vector<std::string> parseLine(std::string line);

  std::string findLabel(std::string line);
  
  void validateLabel(std::string label);
};

#endif // ASSEMBLER_H_INCLUDED
