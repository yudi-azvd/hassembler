#include <iostream>

#include "../../include/simulador.h"

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


bool Simulator::getInputFileContent() { 
  int number;
  std::vector<int16_t> numbers;
  std::fstream infile(_filename);

  if (!infile.is_open()) {
    std::cout << "Arquivo não encontrado " << _filename << std::endl;
    return false;
  }

  while (infile >> number) {
    numbers.push_back(number);
  }

  numbers.shrink_to_fit();
  std::copy(numbers.begin(), numbers.end(), _memory);
  infile.close();
  return true;
}


// Eu posso assumir que a seção de dados vem DEPOIS
// da seção de código.
void Simulator::run() {
  bool ok = getInputFileContent();

  if (!ok) {
    return;
  }

  _pc = 0;
  _acc = 0;
  int address, operand, inputNumber, addrContent;
  bool instructionFound;
  std::string instruction;

  while (_memory[_pc] != 14) { // enquanto não é STOP
    int number = _memory[_pc];
    instructionFound = _reversedOpcodeTable.find(number) 
                    != _reversedOpcodeTable.end();

    if (instructionFound) {
      instruction = _reversedOpcodeTable[number];

      // e se houver pulo?
      // if (instruction == "copy") {
      //   _pc += 3;
      // }
      // else if (instruction == "stop") {
      //   _pc += 1;
      // }
      // else { // add, sub, mul, output, ...
      //   _pc += 2;
      // }

      if (instruction == "add") {
        address = _memory[_pc+1];
        operand = _memory[address];
        _acc += operand;
        _pc += 2;
      }
      else if (instruction == "sub") {
        address = _memory[_pc+1];
        operand = _memory[address];
        _acc -= operand;
        _pc += 2;
      }
      else if (instruction == "mul") {
        address = _memory[_pc+1];
        operand = _memory[address];
        _acc *= operand;
        _pc += 2;
      }
      else if (instruction == "div") {
        address = _memory[_pc+1];
        operand = _memory[address];
        _acc /= operand;
        _pc += 2;
      }
      else if (instruction == "load") {
        address = _memory[_pc+1];
        _acc = _memory[address];
        _pc += 2;
      }
      else if (instruction == "store") {
        address = _memory[_pc+1];
        _memory[address] = _acc;
        _pc += 2;
      }
      else if (instruction == "input") {
        std::cin >> inputNumber;
        address = _memory[_pc+1];
        _memory[address] = inputNumber;
        _pc += 2;
      }
      else if (instruction == "output") {
        address = _memory[_pc+1];
        addrContent = _memory[address];
        // std::cout << "OUTPUT: " << addrContent << std::endl;
        _pc += 2;
      }
      else {
        std::cout << "ALGUM ERRO AÍ" << std::endl;
        std::cout << "não entendi: " << instruction << std::endl;
        return;
      }
    }

    std::cout << "PC <- " << _pc << std::endl;
    std::cout << "ACC <- " << _acc << std::endl;
    if (instruction == "output") {
      std::cout << "OUTPUT: " << addrContent << std::endl;
    }
  }

  // std::cout << "programa chegou em STOP" << std::endl;
}
