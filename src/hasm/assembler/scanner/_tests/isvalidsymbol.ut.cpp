#include <iostream>
#include <vector>

#include "doctest.h"
#include "assembler/scanner/scanner.h"


TEST_SUITE_BEGIN("assembler-scanner-isvalidsymbol");


TEST_CASE("should accept normal words") {
  Scanner scanner;
  CHECK(scanner.isValidSymbol("label"));
  CHECK(scanner.isValidSymbol("banana"));
  CHECK(scanner.isValidSymbol("symbol"));
  CHECK(scanner.isValidSymbol("symbol"));
  CHECK(scanner.isValidSymbol("UPPERCASE"));
}


TEST_CASE("should accept words with '_'") {
  Scanner scanner;
  CHECK(scanner.isValidSymbol("my_label"));
  CHECK(scanner.isValidSymbol("ban_ana"));
  CHECK(scanner.isValidSymbol("word_"));
  CHECK(scanner.isValidSymbol("_symbol"));
}


TEST_CASE("should accept words with numbers") {
  Scanner scanner;
  CHECK(scanner.isValidSymbol("n1"));
  CHECK(scanner.isValidSymbol("ban1234"));
}


TEST_CASE("should not accept words with leading numbers") {
  Scanner scanner;
  CHECK_FALSE(scanner.isValidSymbol("123label"));
  CHECK_FALSE(scanner.isValidSymbol("123LABEL"));
}


TEST_CASE("should accept pure numbers") {
  Scanner scanner;
  CHECK_FALSE(scanner.isValidSymbol("123"));
  CHECK_FALSE(scanner.isValidSymbol("0"));
  CHECK_FALSE(scanner.isValidSymbol("1"));
  CHECK_FALSE(scanner.isValidSymbol("9485"));
}


TEST_CASE("should not accept special characters") {
  Scanner scanner;
  CHECK_FALSE(scanner.isValidSymbol("my@label"));
  CHECK_FALSE(scanner.isValidSymbol("ban_ana#"));
  CHECK_FALSE(scanner.isValidSymbol("wo!rd_"));
  CHECK_FALSE(scanner.isValidSymbol("(_word)"));
}


TEST_CASE("should not accept '-' anywhere in the symbol") {
  Scanner scanner;
  CHECK_FALSE(scanner.isValidSymbol("my-label"));
  CHECK_FALSE(scanner.isValidSymbol("ban-a_na"));
  CHECK_FALSE(scanner.isValidSymbol("-ban-a_na"));
  CHECK_FALSE(scanner.isValidSymbol("word-"));
}


TEST_CASE("should not accept '.' anywhere in the symbol") {
  Scanner scanner;
  CHECK_FALSE(scanner.isValidSymbol("my.label"));
  CHECK_FALSE(scanner.isValidSymbol("ban.a_na"));
  CHECK_FALSE(scanner.isValidSymbol(".ban.a_na"));
  CHECK_FALSE(scanner.isValidSymbol("word."));
}


TEST_CASE("should not accept 'ç' anywhere in the symbol") {
  Scanner scanner;
  CHECK_FALSE(scanner.isValidSymbol("myçlabel"));
  CHECK_FALSE(scanner.isValidSymbol("bança_na"));
  CHECK_FALSE(scanner.isValidSymbol("çbança_na"));
  CHECK_FALSE(scanner.isValidSymbol("wordç"));
}


TEST_CASE("should not accept symbols longer than 50 characters") {
  Scanner scanner;
  std::string veryLongSymbol = "sal_dfjlskjfksljflksjdlfkjsljf"
    "ad_askd_lkas_da_sdk_lasdk";

  INFO("veryLongSymbol length:", veryLongSymbol.size());
  CHECK_FALSE(scanner.isValidSymbol(veryLongSymbol));
}


TEST_SUITE_END();
