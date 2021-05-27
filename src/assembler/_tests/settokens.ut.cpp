// #include <iostream>
// #include <vector>

// #include "doctest/doctest.h"
// #include "assembler/assembler.h"
// #include "util/util.h"


// struct TokenizedLine {
//   std::string label;
//   std::string operation;
//   std::string operand1;
//   std::string operand2;

//   friend std::ostream& operator<<(std::ostream& os, TokenizedLine line) {
//     return os << "label: \"" << line.label
//       << "\", operation: \"" << line.operation
//       << "\", operand1: \"" << line.operand1
//       << "\", operand2: \"" << line.operand2 << "\"";
//   };

//   friend bool operator==(TokenizedLine first, TokenizedLine second) {
//     return first.label == second.label
//       && first.operation == second.operation
//       && first.operand1 == second.operand1
//       && first.operand2 == second.operand2;
//   }
// };


// TokenizedLine getTkLine(std::string line) {
//   TokenizedLine tkLine = {
//     "LABEL", "OPERATION", "OPERAND1", "OPERAND2"
//   };

//   return tkLine;
// }


// struct LineAndTokenizedLine {
//   std::string line;
//   TokenizedLine tkLine;

//   friend std::ostream& operator<<(std::ostream& os, LineAndTokenizedLine latkLine) {
//     return os << "line: " << latkLine.line
//       << latkLine.tkLine;
//   };
// };


// TEST_CASE("settokens") {
//   std::string line = "N1: SPACE";
//   TokenizedLine gotTokenizedLine;

//   std::vector<LineAndTokenizedLine> lines = {
//     {"N1: SPACE", {"N1", "SPACE", "", ""}},

//     {"some_label: copy zero older", {"some_label", "copy", "zero", "older"}},

//     {"some_label: add um", {"some_label", "add", "um", ""}},

//     {"copy zero older", {"", "copy", "zero", "older"}},

//     {"stop", {"", "stop", "", ""}},

//     {"input n2", {"", "input", "n2", ""}},

//     {"b: space", {"b", "space", "", ""}},

//     {"DOIS: CONST 2", {"DOIS", "CONST", "2", ""}},
//   };

//   for (auto lineAndExpectedTokenizedLine : lines) {
//     gotTokenizedLine = getTkLine(lineAndExpectedTokenizedLine.line);

//     INFO("exp: ", lineAndExpectedTokenizedLine.tkLine);
//     INFO("got: ", gotTokenizedLine);

//     CHECK_EQ(lineAndExpectedTokenizedLine.tkLine, gotTokenizedLine);
//   }
// }
