// #ifndef PARSELINE_H_INCLUDED
// #define PARSELINE_H_INCLUDED

// #include <iostream>
// #include <vector>

// struct LineAndItsTokens {
//   std::string line;
//   std::vector<std::string> tokens;

//   friend std::ostream &operator<<(std::ostream& os, const LineAndItsTokens& line);
// };


// /**
//  * @brief Processa uma linha retornando LABEL, OPERAÇÃO, OPERANDO_1 e OPERANDO_2
//  * 
//  * @param[in] line Linha
//  * @return vetor de strings com 0: ROTULO?, 1: OPERAÇÃO, 2: OPERANDO1, 3: OPERANDO2
//  */
// std::vector<std::string> parseLine(std::string line);

// std::string findLabel(std::string line);

// /**
//  * @brief Valida um label (generalizar pra  umm símbolo?)
//  * 
//  * Válidos: n2, N2, __N2
//  */
// void validateLabel(std::string label);


// #endif // !PARSELINE_H_INCLUDED