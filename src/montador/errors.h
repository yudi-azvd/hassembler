#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED 

#include <iostream>
#include <exception>

class SyntaticError : public std::exception {
  std::string message;

public:
  SyntaticError(const std::string& msg) : message(msg) {}

  virtual const char* what() const noexcept override {
    return message.c_str();
  };
};

class LexicalError : public std::exception {
  std::string message;

public:
  LexicalError(const std::string& msg) : message(msg) {}

  virtual const char* what() const noexcept override {
    return message.c_str();
  };
};

#endif