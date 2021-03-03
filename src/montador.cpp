#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

#include "../include/parseline.h"

/*

contador_posição = 0
contador_linha = 1

Enquanto arquivo fonte não chegou ao fim, faça:
  Obtém uma linha do fonte
  Separa os elementos da linha:
    rótulo, operação, operandos, comentários
    Ignora os comentários
  
  Se existe rótulo:
    Procura rótulo na TS (Tabela de Símbolos)
    
    Se achou: 
      Erro => símbolo redefinido
    Senão: 
      Insere rótulo e contador_posição na TS

  Procura operação na tabela de instruções
  
  Se achou:
    contador_posição = contador_posição + tamanho da instrução
  Senão:
    Procura operação na tabela de diretivas
    Se achou:
      chama subrotina que executa a diretiva
      contador_posição = valor retornado pela subrotina
    Senão: 
      Erro, operação não identificada

  contador_linha = contador_linha + 1 ? aqui mesmo?
*/

std::map<std::string, int> opcodeTable {
  {"ADD", 1},
  {"SUB", 2},
  {"MUL", 3},
  {"DIV", 4},
  {"JMP", 5},
  {"JMPN", 6},
  {"JMPP", 7},
  {"JMPZ", 8},
  {"COPY", 9},
  {"LOAD", 10},
  {"STORE", 11},
  {"INPUT", 12},
  {"OUTPUT", 13},
  {"STOP", 14},
};


void assemble(
  std::vector<std::string> sourceFileContent, 
  std::map<std::string, int> symbolTable
) {
  // 1a passada
  int positionCounter = 0;
  int lineCounter = 1;
  std::vector<std::string> tokens;
  std::string label, operation, operand1, operand2;

  for (std::string line : sourceFileContent) {
    std::cout << lineCounter << ": " << line << std::endl;

    // not necessarily length = 0
    // if line is empty: continue; lineCounter++;
    tokens = parseLine(line);
    // if tokens.size() == 0: continue; lineCounter++; // linha vazia
    // doStuffWithTokens(tokens); // teste de unidade
    label = tokens[0];
    operation = tokens[1];
    operand1 = tokens[2];
    operand2 = tokens[3];

    // LABEL
    if (label.length() > 0) {
      bool labelFound = symbolTable.find(label) != symbolTable.end();
      if (!labelFound) {
        symbolTable[label] = positionCounter;
      }
      else {
        // throw error: símbolo definido
      }
    }

    // OPERATION 
    bool operationFound = opcodeTable.find(operation) != opcodeTable.end();
    if (operationFound) {
      // positionCounter += 
      // erro por número errado de operandos?
      positionCounter += 2; // numero de operandos ou tamanho da instrução
    }
    else {
      // procura na tabela de diretivas
      // Se achou:
      //   chama subrotina que executa a diretiva
      //   contador_posição = valor retornado pela subrotina
      // Senão: 
      //   Erro, operação não identificada
    }

    lineCounter++;
  }
}


void showCorrectUsage() {
  std::cout << "Informe o nome do arquivo fonte. Exemplo:" << std::endl;
  std::cout << "$ ./build/montador ./caminho/relativo/pro/seu/arquivo.asm" << std::endl;
}



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
    sourceFileContent.push_back(line);
  }

  // try
  assemble(sourceFileContent, symbolTable);
  // catch (errors)
  // print errors

  return 0;
}

