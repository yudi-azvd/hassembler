#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <iostream>
#include <vector>


class Scanner {
public:
  static std::vector<std::string> parseTokens(std::string line) {
    int newStart = 0;
    int tokenStartsAt = 0;
    std::string token = "";
    std::vector<std::string> tokens;

    while (tokenStartsAt >= 0) {
      token = findNextTokenStartingFrom(newStart, line, tokenStartsAt);
      newStart = tokenStartsAt + token.length();
      tokens.push_back(token);
    }

    tokens.pop_back();
    tokens.shrink_to_fit();

    return tokens;
  }


  static std::string findNextTokenStartingFrom(
    size_t start,
    std::string line,
    int& tokenStartsAt
  ) {
    size_t i;
    char c;
    bool symbolStarted = false,
      isCommentDelimiter, isTokenDelimiter, isWhitespace;
    std::string symbol = "";

    for (i = start; i < line.length(); i++) {
      c = line[i];
      isCommentDelimiter = c == ';';
      isWhitespace = (c == ' ' || c == '\t' || c == '\r');
      isTokenDelimiter = c == ':' || c == ',';

      if (isCommentDelimiter) {
        tokenStartsAt = symbolStarted
          ? i-symbol.length()
          : -1;
        return symbol;
      }

      if (!symbolStarted && isWhitespace) {
        continue;
      }

      if (symbolStarted && (isWhitespace || isTokenDelimiter)) {
        tokenStartsAt = i-symbol.length();
        return symbol;
      }

      if (!isWhitespace) {
        symbolStarted = true;
        symbol.push_back(c);

        if (isTokenDelimiter) {
          tokenStartsAt = i;
          return symbol;
        }
      }
    }

    tokenStartsAt = symbolStarted
      ? i-symbol.length()
      : -1;

    return symbol;
  }


  static bool isValidSymbol(std::string symbol) {
    if (!std::isalpha(symbol[0]) && symbol[0] != '_') {
      return false;
    }

    if (symbol.length() >= 50) {
      return false;
    }

    bool isValidChar = true;
    for (auto c : symbol) {
      isValidChar = std::isalpha(c) || std::isdigit(c) || c == '_';
      if (!isValidChar) {
        return false;
      }
    }

    return true;
  }
};


#endif // SCANNER_H_INCLUDED

/*
*/
