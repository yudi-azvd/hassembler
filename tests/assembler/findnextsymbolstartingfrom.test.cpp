#include <iostream>
#include <vector>

#include "../../lib/doctest/doctest.h"

#include "../../include/errors.h"
#include "../../include/parseline.h"
#include "../../include/assembler.h"


TEST_CASE("findNextTokenStartingFrom") {
  Assembler as; 
  std::string token;

  //                                                !           
  token = as.findNextTokenStartingFrom(9, "OLD_DATA: SPACE");
  CHECK_EQ(token, "SPACE");

  //                                                !           
  token = as.findNextTokenStartingFrom(9, "OLD_DATA: SPACE ");
  CHECK_EQ(token, "SPACE");

  //                                                !           
  token = as.findNextTokenStartingFrom(9, "OLD_DATA  :    SPACE ");
  CHECK_EQ(token, ":");

  //                                       !           
  token = as.findNextTokenStartingFrom(0, "OLD_DATA  :    SPACE ");
  CHECK_EQ(token, "OLD_DATA");
}

TEST_CASE("sequential calls to findNextTokenStartingFrom 1") {
  int start = 0;
  Assembler as; 

  std::string line = "COPY NEW_DATA,OLD_DATA";

  std::string token = "";

  std::vector<std::string> tokens;

  token = as.findNextTokenStartingFrom(0, line);
  start += token.length();
  CHECK_EQ(token, "COPY");
  tokens.push_back(token);

  token = as.findNextTokenStartingFrom(start+1, line);
  start += token.length();
  CHECK_EQ(token, "NEW_DATA,OLD_DATA");
  tokens.push_back(token);
}

TEST_CASE("sequential calls to findNextTokenStartingFrom 2") {
  int start = 0;
  Assembler as; 

  std::string line = "NEW_DATA:SPACE     ";

  std::string token = "";

  std::vector<std::string> tokens;

  token = as.findNextTokenStartingFrom(0, line);
  start += token.length();
  CHECK_EQ(token, "NEW_DATA");
  tokens.push_back(token);

  token = as.findNextTokenStartingFrom(start, line);
  start += token.length();
  CHECK_EQ(token, ":");
  tokens.push_back(token);

  token = as.findNextTokenStartingFrom(start, line);
  start += token.length();
  CHECK_EQ(token, "SPACE");
  tokens.push_back(token);
}

TEST_CASE("sequential calls to findNextTokenStartingFrom 3") {
  int start = 0;
  Assembler as; 

  // dá ruim pq start não conta a posição inicial to token
  std::string line = "      NEW_DATA:SPACE     ";

  std::string token = "";

  std::vector<std::string> tokens;

  token = as.findNextTokenStartingFrom(0, line);
  start += token.length();
  CHECK_EQ(token, "NEW_DATA");
  tokens.push_back(token);

  token = as.findNextTokenStartingFrom(start, line);
  // dá ruim pq start não conta a posição inicial to token
  start += token.length();
  CHECK_EQ(token, ":");
  tokens.push_back(token);

  token = as.findNextTokenStartingFrom(start, line);
  start += token.length();
  CHECK_EQ(token, "SPACE");
  tokens.push_back(token);
}

TEST_CASE("sequential calls to findNextTokenStartingFrom 4 - comment") {
  int start = 0;
  Assembler as; 

  std::string line = "NEW_DATA:SPACE  ; tem qie ser ignorado";

  std::string token = "";

  std::vector<std::string> tokens;

  token = as.findNextTokenStartingFrom(0, line);
  start += token.length();
  CHECK_EQ(token, "NEW_DATA");
  tokens.push_back(token);

  token = as.findNextTokenStartingFrom(start, line);
  start += token.length();
  CHECK_EQ(token, ":");
  tokens.push_back(token);

  token = as.findNextTokenStartingFrom(start, line);
  start += token.length();
  CHECK_EQ(token, "SPACE");
  tokens.push_back(token);

  // vai começar o comentário

  token = as.findNextTokenStartingFrom(start, line);
  start += token.length();
  CHECK_EQ(token, "");
  tokens.push_back(token);
}

/**
 * run findnextoken()
 * while token != ";"
 * e as linhas sem comentários?
 */
