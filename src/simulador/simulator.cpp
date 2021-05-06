#include <iostream>

#include "simulator.h"

Simulator::Simulator(std::string filename) {
  _filename = filename;
  _reversedOpcodeTable = {
    {1, "add"},
    {2, "sub"},
    {3, "mul"},
    {4, "div"},
    {5, "jmp"},
    {6, "jmpn"},
    {7, "jmpp"},
    {8, "jmpz"},
    {9, "copy"},
    {10, "load"},
    {11, "store"},
    {12, "input"},
    {13, "output"},
    {14, "stop"},
  };
}


Simulator::~Simulator() {}


void Simulator::run() {
  bool ok = getInputFileContent();

  if (!ok) {
    return;
  }
 
  simulate();

  generateOutput();
}


bool Simulator::getInputFileContent() { 
  int number;
  std::vector<int16_t> numbers(MEM_MAX_SIZE);
  // std::vector<int16_t> numbers;
  std::fstream infile(_filename);

  if (!infile.is_open()) {
    std::cout << "Arquivo não encontrado " << _filename << std::endl;
    return false;
  }

  int i = 0;
  while (infile >> number) {
    numbers[i++] = number;
  }

  numbers.shrink_to_fit();
  std::copy(numbers.begin(), numbers.end(), _memory);
  infile.close();
  return true;
}


// Eu posso assumir que a seção de dados vem DEPOIS
// da seção de código.
void Simulator::simulate() {
  _pc = 0;
  _acc = 0;
  int address1, address2, operand1, inputNumber, addrContent1{};
  bool instructionFound;
  std::string instruction;

  while (_memory[_pc] != 14) { // enquanto não é STOP
    int number = _memory[_pc];
    instructionFound = _reversedOpcodeTable.find(number) 
                    != _reversedOpcodeTable.end();

    if (instructionFound) {
      instruction = _reversedOpcodeTable[number];

      if (instruction == "add") {
        address1 = _memory[_pc+1];
        operand1 = _memory[address1];
        _acc += operand1;
        _pc += 2;
      }
      else if (instruction == "sub") {
        address1 = _memory[_pc+1];
        operand1 = _memory[address1];
        _acc -= operand1;
        _pc += 2;
      }
      else if (instruction == "mul") {
        address1 = _memory[_pc+1];
        operand1 = _memory[address1];
        _acc *= operand1;
        _pc += 2;
      }
      else if (instruction == "div") {
        address1 = _memory[_pc+1];
        operand1 = _memory[address1];
        _acc /= operand1;
        _pc += 2;
      }
      else if (instruction == "jmp") {
        address1 = _memory[_pc+1];
        _pc = address1;
      }
      else if (instruction == "jmpn") {
        if (_acc < 0) {
          address1 = _memory[_pc+1];
          _pc = address1;
        }
        else {
          _pc += 2;
        }
      }
      else if (instruction == "jmpp") {
        if (_acc > 0) {
          address1 = _memory[_pc+1];
          _pc = address1;
        }
        else {
          _pc += 2;
        }
      }
      else if (instruction == "jmpz") {
        if (_acc == 0) {
          address1 = _memory[_pc+1];
          _pc = address1;
        }
        else {
          _pc += 2;
        }
      }
      else if (instruction == "copy") {
        address1 = _memory[_pc+1];
        address2 = _memory[_pc+2];
        addrContent1 = _memory[address1];
        _memory[address2] = addrContent1;
        _pc += 3;
      }
      else if (instruction == "load") {
        address1 = _memory[_pc+1];
        _acc = _memory[address1];
        _pc += 2;
      }
      else if (instruction == "store") {
        address1 = _memory[_pc+1];
        _memory[address1] = _acc;
        _pc += 2;
      }
      else if (instruction == "input") {
        std::cin >> inputNumber;
        address1 = _memory[_pc+1];
        _memory[address1] = inputNumber;
        _pc += 2;
      }
      else if (instruction == "output") {
        address1 = _memory[_pc+1];
        addrContent1 = _memory[address1];
        // std::cout << "OUTPUT: " << addrContent1 << std::endl;
        _pc += 2;
      }
      else {
        std::cout << "ALGUM ERRO AÍ" << std::endl;
        std::cout << "não entendi: " << instruction << std::endl;
        return;
      }
    }

    // _logs.push_back(essas strings aí)
    std::cout << "PC <- " << _pc << std::endl;
    std::cout << "ACC <- " << _acc << std::endl;
    if (instruction == "output") {
      std::cout << "OUTPUT: " << addrContent1 << std::endl;
      _outputs.push_back(addrContent1);
    }
  }

  // std::cout << "programa chegou em STOP" << std::endl;
  std::cout << "PC <- " << _pc << std::endl;
  std::cout << "ACC <- " << _acc << std::endl;
}


void Simulator::generateOutput() {
  if (_outputs.size() == 0) {
    return;
  }

  std::string finalString = "", outFilename = "";
  bool insertMode = false;
  for (int i = _filename.size() - 1; i >= 0; --i) {
    if (insertMode) {
      outFilename.insert(0, 1, _filename[i]);
    }

    if (_filename[i] == '/') {
      break;
    }

    if (_filename[i] == '.') {
      insertMode = true;
      continue;
    }
  }

  if (outFilename[0] != '/') { // "nome" => "/nome"
    outFilename.insert(0, 1, '/');
  }

  outFilename.insert(0, "."); // "/nome" => "./nome"
  outFilename.append(".out"); // "./nome.out"

  std::fstream outputFile;
  outputFile.open(outFilename, std::ios::out);

  for (auto number : _outputs) {
    finalString.append(std::to_string(number) + "\n");
  }

  outputFile << finalString;
  outputFile.close();
}
