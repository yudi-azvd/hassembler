/**
 * Aprendi aqui:
 * https://www.learncpp.com/cpp-tutorial/exceptions-classes-and-inheritance/
 */

#ifndef HASMPARAMETEREXCEPTION_H_INCLUDED
#define HASMPARAMETEREXCEPTION_H_INCLUDED

#include <iostream>
#include <exception>

#include "hasmexception.h"

class HasmParameterException : public HasmException {
public:
  HasmParameterException(std::string m) {
    msg = "error: " +  m;
  }

  const char* what() const noexcept override {
    return msg.c_str();
  }

private:
  std::string msg;
};


#endif // HASMPARAMETEREXCEPTION_H_INCLUDED
