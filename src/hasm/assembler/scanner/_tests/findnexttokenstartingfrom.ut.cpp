#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/scanner/scanner.h"


TEST_SUITE_BEGIN("assembler-scanner-findnexttoken");


TEST_CASE("basic cases") {
  Scanner scanner;
  int tokenStartsAt = 0;
  std::string token;

  //                                                !
  token = scanner.findNextTokenStartingFrom(9, "OLD_DATA: SPACE", tokenStartsAt);
  CHECK_EQ(token, "SPACE");
  CHECK_EQ(tokenStartsAt, 10);

  //                                                !
  token = scanner.findNextTokenStartingFrom(9, "OLD_DATA: SPACE ", tokenStartsAt);
  CHECK_EQ(token, "SPACE");

  //                                                !
  token = scanner.findNextTokenStartingFrom(9, "OLD_DATA  :    SPACE ", tokenStartsAt);
  CHECK_EQ(token, ":");
  CHECK_EQ(tokenStartsAt, 10);

  //                                       !
  token = scanner.findNextTokenStartingFrom(0, "OLD_DATA  :    SPACE ", tokenStartsAt);
  CHECK_EQ(token, "OLD_DATA");
  CHECK_EQ(tokenStartsAt, 0);
}


TEST_CASE("sequential calls 1") {
  Scanner scanner;
  int newStart = 0;
  int tokenStartsAt = 0;
  std::string line = "COPY NEW_DATA,OLD_DATA";
  std::string token = "";

  token = scanner.findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "COPY");
  CHECK_EQ(tokenStartsAt, 0);

  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "NEW_DATA");
  CHECK_EQ(tokenStartsAt, 5);

  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, ",");
  CHECK_EQ(tokenStartsAt, 13);

  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "OLD_DATA");
  CHECK_EQ(tokenStartsAt, 14);
}


TEST_CASE("sequential calls 2") {
  Scanner scanner;
  int newStart = 0;
  int tokenStartsAt = 0;
  std::string line = "NEW_DATA:SPACE     ";
  std::string token = "";

  token = scanner.findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "NEW_DATA");
  CHECK_EQ(tokenStartsAt, 0);

  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, ":");
  CHECK_EQ(tokenStartsAt, 8);

  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "SPACE");
}


TEST_CASE("sequential calls 3") {
  Scanner scanner;
  int newStart = 0;
  int tokenStartsAt = 0;

  std::string line = "      NEW_DATA:SPACE     ";
  std::string token = "";
  std::vector<std::string> tokens;

  token = scanner.findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "NEW_DATA");
  CHECK_EQ(tokenStartsAt, 6);

  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, ":");
  CHECK_EQ(tokenStartsAt, 14);

  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "SPACE");
  CHECK_EQ(tokenStartsAt, 15);


  line = "\tNEW_DATA  :   SPACE     ";

  token = scanner.findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "NEW_DATA");
  CHECK_EQ(tokenStartsAt, 1);

  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, ":");
  CHECK_EQ(tokenStartsAt, 11);

  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "SPACE");
  CHECK_EQ(tokenStartsAt, 15);
}


TEST_CASE("sequential calls 4 - comment") {
  Scanner scanner;
  int newStart = 0;
  int tokenStartsAt = 0;
  std::string line = "NEW_DATA:SPACE  ; tem qie ser ignorado";
  std::string token = "";

  token = scanner.findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "NEW_DATA");

  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, ":");

  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "SPACE");

  // vai começar o comentário

  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "");
}


TEST_CASE("should not find tokens at the end of the line") {
  Scanner scanner;
  int newStart = 0;
  int tokenStartsAt = 0;
  std::string line = "COPY    NEW_DATA,OLD_DATA";
  std::string token = "";

  token = scanner.findNextTokenStartingFrom(17, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "OLD_DATA");
  CHECK_EQ(tokenStartsAt, 17);

  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "");
  CHECK_EQ(tokenStartsAt, -1);


  line = "NEW_DATA:SPACE  ; tem qie ser ignorado";

  int semiColonPosition = 16;
  token = scanner.findNextTokenStartingFrom(semiColonPosition, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "");
  CHECK_EQ(tokenStartsAt, -1);


  line = "NEW_DATA:SPACE     ";

  newStart = 15;
  token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "");
  CHECK_EQ(tokenStartsAt, -1);
}


TEST_CASE("should work in iterative calls") {
  Scanner scanner;
  int newStart = 0;
  int tokenStartsAt = 0;
  std::string line = "COPY    NEW_DATA,OLD_DATA";
  std::string token = "";
  std::vector<std::string> expectedtokens = {"COPY", "NEW_DATA", ",", "OLD_DATA"};
  std::vector<std::string> gotTokens;

  while (tokenStartsAt >= 0) {
    token = scanner.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
    newStart = tokenStartsAt + token.length();
    gotTokens.push_back(token);
  }

  gotTokens.pop_back();
  CHECK_EQ(gotTokens, expectedtokens);
}


TEST_SUITE_END();
