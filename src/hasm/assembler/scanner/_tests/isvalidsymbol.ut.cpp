#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/scanner/scanner.h"


TEST_SUITE_BEGIN("assembler-scanner-isvalidsymbol");


TEST_CASE("should accept normal words") {
  CHECK(Scanner::isValidSymbol("label"));
  CHECK(Scanner::isValidSymbol("banana"));
  CHECK(Scanner::isValidSymbol("symbol"));
  CHECK(Scanner::isValidSymbol("symbol"));
  CHECK(Scanner::isValidSymbol("UPPERCASE"));
}


TEST_CASE("should accept words with '_'") {
  CHECK(Scanner::isValidSymbol("my_label"));
  CHECK(Scanner::isValidSymbol("ban_ana"));
  CHECK(Scanner::isValidSymbol("word_"));
  CHECK(Scanner::isValidSymbol("_symbol"));
}


TEST_CASE("should accept words with numbers") {
  CHECK(Scanner::isValidSymbol("n1"));
  CHECK(Scanner::isValidSymbol("ban1234"));
}


TEST_CASE("should not accept words with leading numbers") {
  CHECK_FALSE(Scanner::isValidSymbol("123label"));
  CHECK_FALSE(Scanner::isValidSymbol("123LABEL"));
}


TEST_CASE("should accept pure numbers") {
  CHECK_FALSE(Scanner::isValidSymbol("123"));
  CHECK_FALSE(Scanner::isValidSymbol("0"));
  CHECK_FALSE(Scanner::isValidSymbol("1"));
  CHECK_FALSE(Scanner::isValidSymbol("9485"));
}


TEST_CASE("should not accept special characters") {
  CHECK_FALSE(Scanner::isValidSymbol("my@label"));
  CHECK_FALSE(Scanner::isValidSymbol("ban_ana#"));
  CHECK_FALSE(Scanner::isValidSymbol("wo!rd_"));
  CHECK_FALSE(Scanner::isValidSymbol("(_word)"));
}


TEST_CASE("should not accept '-' anywhere in the symbol") {
  CHECK_FALSE(Scanner::isValidSymbol("my-label"));
  CHECK_FALSE(Scanner::isValidSymbol("ban-a_na"));
  CHECK_FALSE(Scanner::isValidSymbol("-ban-a_na"));
  CHECK_FALSE(Scanner::isValidSymbol("word-"));
}


TEST_CASE("should not accept '.' anywhere in the symbol") {
  CHECK_FALSE(Scanner::isValidSymbol("my.label"));
  CHECK_FALSE(Scanner::isValidSymbol("ban.a_na"));
  CHECK_FALSE(Scanner::isValidSymbol(".ban.a_na"));
  CHECK_FALSE(Scanner::isValidSymbol("word."));
}


TEST_CASE("should not accept 'ç' anywhere in the symbol") {
  CHECK_FALSE(Scanner::isValidSymbol("myçlabel"));
  CHECK_FALSE(Scanner::isValidSymbol("bança_na"));
  CHECK_FALSE(Scanner::isValidSymbol("çbança_na"));
  CHECK_FALSE(Scanner::isValidSymbol("wordç"));
}


TEST_CASE("should not accept symbols longer than 50 characters") {
  std::string veryLongSymbol = "sal_dfjlskjfksljflksjdlfkjsljf"
    "ad_askd_lkas_da_sdk_lasdk";

  INFO("veryLongSymbol length:", veryLongSymbol.size());
  CHECK_FALSE(Scanner::isValidSymbol(veryLongSymbol));
}


TEST_SUITE_END();
