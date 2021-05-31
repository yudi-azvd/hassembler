#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/oldassembler.h"
#include "assembler/scanner/scanner.h"


TEST_CASE("basic cases") {
  int tokenStartsAt = 0;
  std::string token;

  //                                                !
  token = Scanner::findNextTokenStartingFrom(9, "OLD_DATA: SPACE", tokenStartsAt);
  CHECK_EQ(token, "SPACE");
  CHECK_EQ(tokenStartsAt, 10);

  //                                                !
  token = Scanner::findNextTokenStartingFrom(9, "OLD_DATA: SPACE ", tokenStartsAt);
  CHECK_EQ(token, "SPACE");

  //                                                !
  token = Scanner::findNextTokenStartingFrom(9, "OLD_DATA  :    SPACE ", tokenStartsAt);
  CHECK_EQ(token, ":");
  CHECK_EQ(tokenStartsAt, 10);

  //                                       !
  token = Scanner::findNextTokenStartingFrom(0, "OLD_DATA  :    SPACE ", tokenStartsAt);
  CHECK_EQ(token, "OLD_DATA");
  CHECK_EQ(tokenStartsAt, 0);
}


TEST_CASE("sequential calls 1") {
  int newStart = 0;
  int tokenStartsAt = 0;
  std::string line = "COPY NEW_DATA,OLD_DATA";
  std::string token = "";

  token = Scanner::findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "COPY");
  CHECK_EQ(tokenStartsAt, 0);

  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "NEW_DATA");
  CHECK_EQ(tokenStartsAt, 5);

  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, ",");
  CHECK_EQ(tokenStartsAt, 13);

  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "OLD_DATA");
  CHECK_EQ(tokenStartsAt, 14);
}


TEST_CASE("sequential calls 2") {
  int newStart = 0;
  int tokenStartsAt = 0;
  std::string line = "NEW_DATA:SPACE     ";
  std::string token = "";

  token = Scanner::findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "NEW_DATA");
  CHECK_EQ(tokenStartsAt, 0);

  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, ":");
  CHECK_EQ(tokenStartsAt, 8);

  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "SPACE");
}


TEST_CASE("sequential calls 3") {
  int newStart = 0;
  int tokenStartsAt = 0;

  std::string line = "      NEW_DATA:SPACE     ";
  std::string token = "";
  std::vector<std::string> tokens;

  token = Scanner::findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "NEW_DATA");
  CHECK_EQ(tokenStartsAt, 6);

  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, ":");
  CHECK_EQ(tokenStartsAt, 14);

  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "SPACE");
  CHECK_EQ(tokenStartsAt, 15);


  line = "\tNEW_DATA  :   SPACE     ";

  token = Scanner::findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "NEW_DATA");
  CHECK_EQ(tokenStartsAt, 1);

  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, ":");
  CHECK_EQ(tokenStartsAt, 11);

  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "SPACE");
  CHECK_EQ(tokenStartsAt, 15);
}


TEST_CASE("sequential calls 4 - comment") {
  int newStart = 0;
  int tokenStartsAt = 0;
  std::string line = "NEW_DATA:SPACE  ; tem qie ser ignorado";
  std::string token = "";

  token = Scanner::findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "NEW_DATA");

  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, ":");

  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "SPACE");

  // vai começar o comentário

  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "");
}


TEST_CASE("should not find tokens at the end of the line") {
  int newStart = 0;
  int tokenStartsAt = 0;
  std::string line = "COPY    NEW_DATA,OLD_DATA";
  std::string token = "";

  token = Scanner::findNextTokenStartingFrom(17, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "OLD_DATA");
  CHECK_EQ(tokenStartsAt, 17);

  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "");
  CHECK_EQ(tokenStartsAt, -1);


  line = "NEW_DATA:SPACE  ; tem qie ser ignorado";

  int semiColonPosition = 16;
  token = Scanner::findNextTokenStartingFrom(semiColonPosition, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "");
  CHECK_EQ(tokenStartsAt, -1);


  line = "NEW_DATA:SPACE     ";

  newStart = 15;
  token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = tokenStartsAt + token.length();
  CHECK_EQ(token, "");
  CHECK_EQ(tokenStartsAt, -1);
}


TEST_CASE("should work in iterative calls") {
  int newStart = 0;
  int tokenStartsAt = 0;
  std::string line = "COPY    NEW_DATA,OLD_DATA";
  std::string token = "";
  std::vector<std::string> expectedtokens = {"COPY", "NEW_DATA", ",", "OLD_DATA"};
  std::vector<std::string> gotTokens;

  while (tokenStartsAt >= 0) {
    token = Scanner::findNextTokenStartingFrom(newStart, line, tokenStartsAt);
    newStart = tokenStartsAt + token.length();
    gotTokens.push_back(token);
  }

  gotTokens.pop_back();
  CHECK_EQ(gotTokens, expectedtokens);
}
