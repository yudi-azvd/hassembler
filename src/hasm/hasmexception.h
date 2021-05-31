#ifndef HASMEXCEPTION_H_INCLUDED
#define HASMEXCEPTION_H_INCLUDED

#include <iostream>
#include <exception>


class HasmException : public std::exception {
public:
  HasmException() {};

  HasmException(std::string m) {
    msg = "error: " +  m;
  }

  const char* what() const noexcept override {
    return msg.c_str();
  }

private:
  std::string msg;
};


#endif // HASMEXCEPTION_H_INCLUDED
