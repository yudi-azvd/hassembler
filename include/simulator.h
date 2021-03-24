#ifndef SIMULADOR_H_INCLUDED
#define SIMULADOR_H_INCLUDED

#include <fstream>
#include <vector>
#include <map>


class Simulator {
private:
  static const int MEM_MAX_SIZE = 216;

  int _pc, _acc;

  std::vector<int> _outputs;

  std::map<int, std::string> _reversedOpcodeTable;

  std::string _filename;

  int16_t _memory[MEM_MAX_SIZE];

  bool getInputFileContent();

public:
  Simulator(std::string filename);

  ~Simulator();

  void run();

  void simulate();

  void generateOutput();
};

#endif // SIMULADOR_H_INCLUDED
