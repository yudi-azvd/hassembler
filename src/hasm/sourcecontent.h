#ifndef SOURCECONTENT_H_INCLUDED
#define SOURCECONTENT_H_INCLUDED

#include <iostream>
#include <vector>

#include "line.h"

class SourceContent {
public:
  // SourceContent(std::vector<Line> ls);

  SourceContent(std::vector<const char*> ls);

  friend std::ostream& operator<<(std::ostream& os, const SourceContent& content) {
    for (auto line : content.lines) {
      os << (line.isDisabled() ? "-" : "+");
      os << line.getContent();
    }

    return os;
  }


  ~SourceContent();

  std::vector<Line> getLines();

private:
  std::vector<Line> lines;
};

#endif // SOURCECONTENT_H_INCLUDED
