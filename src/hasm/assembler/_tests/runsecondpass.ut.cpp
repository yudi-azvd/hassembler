// #include <iostream>
// #include <vector>

// #include "doctest.h"
// #include "assembler/oldassembler.h"
// #include "util/util.h"


// TEST_SUITE_BEGIN("oldassembler-runsecondpass");


// TEST_CASE("rsp print number") {
//   std::vector<std::string> sourceFileContent = {
//     "input b",
//     "output b",
//     "B: SPACE",
//   };

//   std::map<std::string, int> symbolTable = {
//     {"b", 4}
//   };

//   OldAssembler as;
//   as.setSourceFileContent(sourceFileContent);

//   std::vector<int> gotObjectCode;
//   std::vector<int> expectedObjectCode = {
//     12, 4, 13, 4, 0
//   };

//   as.setSymbolTable(symbolTable);
//   as.runSecondPass(sourceFileContent);
//   gotObjectCode = as.objectCode();

//   INFO("exp: ", vectorToString(expectedObjectCode));
//   INFO("got: ", vectorToString(gotObjectCode));
//   INFO("errors: ", vectorToString(as.errors()));

//   CHECK_EQ(gotObjectCode, expectedObjectCode);
// }


// TEST_CASE("rsp add two numbers") {
//   std::vector<std::string> sourceFileContent = {
//     "INPUT N1",
//     "INPUT N2",
//     "LOAD N1",
//     "ADD N2",
//     "",
//     "STORE N3",
//     "OUTPUT N3",
//     "STOP",
//     "N1: SPACE ; SPACE eh uma diretiva. uma funcao deve ser chamada ",
//     "N2: SPACE ; e retornar uma nova posicao",
//     "N3: SPACE",
//   };

//   std::map<std::string, int> symbolTable = {
//     {"n1", 13},
//     {"n2", 14},
//     {"n3", 15},
//   };

//   OldAssembler as;
//   as.setSourceFileContent(sourceFileContent);

//   std::vector<int> gotObjectCode;
//   std::vector<int> expectedObjectCode = {
//     12, 13, 12, 14, 10, 13, 1, 14, 11, 15, 13, 15, 14, 0, 0, 0
//   };

//   as.setSymbolTable(symbolTable);
//   as.runSecondPass(sourceFileContent);
//   gotObjectCode = as.objectCode();

//   INFO("exp: ", vectorToString(expectedObjectCode));
//   INFO("got: ", vectorToString(gotObjectCode));
//   INFO("err: ", vectorToString(as.errors()));

//   CHECK_EQ(gotObjectCode, expectedObjectCode);
// }


// TEST_CASE("rsp print and add number") {
//   std::vector<std::string> sourceFileContent = {
//     "input b",
//     "add dois",
//     "output b",
//     "B: SPACE",
//     "DOIS: const 2"
//   };

//   std::map<std::string, int> symbolTable = {
//     {"b", 6},
//     {"dois", 7},
//   };

//   OldAssembler as;
//   as.setSourceFileContent(sourceFileContent);

//   std::vector<int> gotObjectCode;
//   std::vector<int> expectedObjectCode = {
//     12, 6, 1, 7, 13, 6, 0, 2
//   };

//   as.setSymbolTable(symbolTable);
//   as.runSecondPass(sourceFileContent);
//   gotObjectCode = as.objectCode();

//   INFO("exp: ", vectorToString(expectedObjectCode));
//   INFO("got: ", vectorToString(gotObjectCode));

//   CHECK_EQ(gotObjectCode, expectedObjectCode);
// }


// TEST_CASE("rsp fibonacci") {
//   std::map<std::string, int> symbolTable = {
//     {"front", 10},
//     {"final", 30},
//     {"zero", 33},
//     {"one", 34},
//     {"older", 35},
//     {"old", 36},
//     {"new", 37},
//     {"limit", 38},
//   };

//   std::vector<std::string> sourceFileContent = {
//     "section TEXT",
//     "        COPY ZERO,OLDER",
//     "        COPY ONE,OLD",
//     "        INPUT LIMIT",
//     "        OUTPUT OLD",
//     "FRONT:  LOAD OLDER",
//     "        ADD OLD",
//     "        STORE NEW",
//     "        SUB LIMIT",
//     "        JMPP FINAL",
//     "        OUTPUT NEW",
//     "        COPY OLD,OLDER",
//     "        COPY NEW,OLD",
//     "        JMP FRONT",
//     "FINAL:  OUTPUT LIMIT",
//     "        STOP",
//     "section data",
//     "ZERO:   CONST 0",
//     "ONE:    CONST 1",
//     "OLDER:  SPACE",
//     "OLD:    SPACE",
//     "NEW:    SPACE",
//     "LIMIT:  SPACE",
//   };

//   OldAssembler as;
//   as.setSourceFileContent(sourceFileContent);

//   std::vector<int> gotObjectCode;
//   std::vector<int> expectedObjectCode = {
//     9, 33, 35, 9, 34, 36, 12, 38, 13, 36, 10, 35, 1, 36, 11, 37, 2, 38, 7, 30, 13, 37, 9, 36, 35, 9, 37, 36, 5, 10, 13, 38, 14, 0, 1, 0, 0, 0, 0
//   };

//   as.setSymbolTable(symbolTable);
//   as.runSecondPass(sourceFileContent);
//   gotObjectCode = as.objectCode();

//   INFO("exp: ", vectorToString(expectedObjectCode));
//   INFO("got: ", vectorToString(gotObjectCode));

//   CHECK_EQ(gotObjectCode, expectedObjectCode);
// }


// TEST_CASE("rsp fatorial") {
//   std::map<std::string, int> symbolTable = {
//     {"fat", 4},
//     {"fim", 18},
//     {"aux", 21},
//     {"n", 22},
//     {"one", 23},
//   };

//   std::vector<std::string> sourceFileContent = {
//     "        input n",
//     "        load n",
//     "fat:    sub one",
//     "        jmpz fim",
//     "        store aux",
//     "        mul n",
//     "        store n",
//     "        load aux",
//     "        jmp fat",
//     "fim:    output n",
//     "        stop",
//     "aux:    space",
//     "n:      space",
//     "one:    const 1",
//   };

//   OldAssembler as;
//   as.setSourceFileContent(sourceFileContent);

//   std::vector<int> gotObjectCode;
//   std::vector<int> expectedObjectCode = {
//     12, 22, 10, 22, 2, 23, 8, 18, 11, 21, 3,
//     22, 11, 22, 10, 21, 5, 4, 13, 22, 14, 0, 0, 1
//   };

//   as.setSymbolTable(symbolTable);
//   as.runSecondPass(sourceFileContent);
//   gotObjectCode = as.objectCode();

//   INFO("exp: ", vectorToString(expectedObjectCode));
//   INFO("got: ", vectorToString(gotObjectCode));

//   CHECK_EQ(gotObjectCode, expectedObjectCode);
// }


// TEST_CASE("rsp should add errors undefined operands") {
//   std::map<std::string, int> symbolTable = {
//     {"label", 7},
//   };


//   std::vector<std::string> sourceFileContent = {
//     "input n1",
//     "store n2", // Quantidade de operandos errada!
//     "load LABEL",
//     "jmp FAT",
//     "LABEL: space",
//   };

//   OldAssembler as;

//   as.setSymbolTable(symbolTable);
//   as.setSourceFileContent(sourceFileContent);
//   as.runSecondPass(sourceFileContent);

//   std::vector<std::string> errors = as.errors();

//   INFO("err: ", vectorToString(errors));
//   INFO("symbolTable: ", strToIntMapToString(as.symbolTable()));

//   CHECK_EQ(3, errors.size());
//   CHECK(findErrorWith("Erro Semântico, linha 1: operando 'n1' indefinido", errors));
//   CHECK(findErrorWith("Erro Semântico, linha 2: operando 'n2' indefinido", errors));
//   CHECK(findErrorWith("Erro Semântico, linha 4: operando 'FAT' indefinido", errors));

//   CHECK_FALSE(findErrorWith("Erro Semântico, linha 3: operando 'LABEL' indefinido.", errors));
// }


// TEST_CASE("rsp should add errors with wrong number of operands") {
//   std::map<std::string, int> symbolTable = {
//     {"fat", 4},
//     {"fim", 18},
//     {"aux", 21},
//     {"n", 22},
//     {"one", 23},
//     {"random", 24},
//   };

//   std::vector<std::string> sourceFileContent = {
//     "        input n",
//     "        load n",
//     "fat:    sub one",
//     "        jmpz", // ERRO
//     "        store aux",
//     "        mul n",
//     "",
//     "        store n n", //ERRO
//     "        load aux",
//     "        jmp fat",
//     "fim:    output n",
//     "        stop",
//     "aux:    space 1", // ERRO
//     "n:      space",
//     "one:    const 1",
//     "random:    const ", // ERRO
//   };

//   OldAssembler as;

//   as.setSymbolTable(symbolTable);
//   as.setSourceFileContent(sourceFileContent);
//   as.runSecondPass(sourceFileContent);

//   std::vector<std::string> errors = as.errors();

//   INFO("errors: ", vectorToString(errors));

//   REQUIRE_EQ(4, errors.size());

//   CHECK_EQ(errors[0], "Erro Sintático, linha 4: instrução 'jmpz' com número de operandos errado.");
//   CHECK_EQ(errors[1], "Erro Sintático, linha 8: instrução 'store' com número de operandos errado.");
//   CHECK_EQ(errors[2], "Erro Sintático, linha 13: diretiva 'space' com número de operandos errado.");
//   CHECK_EQ(errors[3], "Erro Sintático, linha 16: diretiva 'const' com número de operandos errado.");
// }


// TEST_CASE("should give errors saying operand should be another type") {
//   std::map<std::string, int> symbolTable = {
//     {"label1", 0}, // não faz diferença o valor do rótulo para esses testes
//   };

//   std::vector<std::string> sourceFileContent = {
//     "fat:    sub 1", // erro
//     "        mul 5", // erro
//     "fim:    output 4", // erro
//     "o:      copy 10,label1", // erro
//     "o2:      copy label1 , 13", // erro
//     "label1: space",
//     "label2: const trinta", // erro
//   };

//   OldAssembler as;

//   as.setSymbolTable(symbolTable);
//   as.setSourceFileContent(sourceFileContent);
//   as.runSecondPass(sourceFileContent);

//   std::vector<std::string> errors = as.errors();

//   INFO("errors: ", vectorToString(errors));

//   REQUIRE_EQ(6, errors.size());

//   CHECK_EQ(errors[0], "Erro Sintático, linha 1: operando '1' deve ser um rótulo.");
//   CHECK_EQ(errors[1], "Erro Sintático, linha 2: operando '5' deve ser um rótulo.");
//   CHECK_EQ(errors[2], "Erro Sintático, linha 3: operando '4' deve ser um rótulo.");
//   CHECK_EQ(errors[3], "Erro Sintático, linha 4: operando '10' deve ser um rótulo.");
//   CHECK_EQ(errors[4], "Erro Sintático, linha 5: operando '13' deve ser um rótulo.");
//   CHECK_EQ(errors[5], "Erro Sintático, linha 7: operando 'trinta' deve ser um inteiro.");
// }


// TEST_CASE("rsp label alone in line should work for instructions") {
//   std::vector<std::string> sourceFileContent = {
//     "section text",
//     "input N",
//     "VALID_LABEL: ",
//     "",
//     "store N",
//     "jmpz VALID_LABEL",
//     "section data",
//     "N: space",
//   };

//   OldAssembler as;

//   as.setSourceFileContent(sourceFileContent);
//   as.runZerothPass();
//   as.runFirstPass(sourceFileContent);
//   // Não precisa ajustar porque SECTIONS estão na ordem correta
//   // as.adjustForDataSection();
//   as.runSecondPass(sourceFileContent);

//   std::map<std::string, int> gotSymbolTable = as.symbolTable();
//   std::map<std::string, int> expectedSymbolTable = {
//     {"valid_label", 2},
//     {"n", 6},
//   };

//   INFO("exp: ", strToIntMapToString(expectedSymbolTable));
//   INFO("got: ", strToIntMapToString(gotSymbolTable));
//   // INFO("got: ", vectorToString(as.errors()));

//   CHECK_EQ(0, as.errors().size());
//   CHECK_EQ(gotSymbolTable, expectedSymbolTable);
// }


// TEST_SUITE_END();
