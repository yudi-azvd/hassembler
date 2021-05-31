#ifndef ASSEMBLYERROR_H_INCLUDED
#define ASSEMBLYERROR_H_INCLUDED

#include <iostream>

#include "hasm/hasmerror.h"


class AssemblyError : public HasmError {
public:
  AssemblyError(int ln, std::string msg) {
    filename = "";
    line = ln;
    message = msg;
  }

  AssemblyError(std::string fn, int ln, std::string msg) {
    filename = fn;
    line = ln;
    message = msg;
  }

  ~AssemblyError() {}

  friend bool operator==(const AssemblyError& lhs, const AssemblyError& rhs) {
    return lhs.filename == rhs.filename &&
      lhs.line == rhs.line &&
      lhs.message == rhs.message;
  }

  friend std::ostream& operator<<(std::ostream& os, const AssemblyError& e) {
    return os << "assembly error: "
      << (e.filename) << ":" <<
      e.line << ": " << e.message;
  }

private:
  std::string message;

  std::string filename;

  int line;
};


#endif // ASSEMBLYERROR_H_INCLUDED
