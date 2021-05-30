#include "sourcecontent.h"


// SourceContent::SourceContent(std::vector<Line> ls)
//   : lines{ls}
// {}


SourceContent::SourceContent(std::vector<const char*> ls) {
  lines.reserve(ls.size());
  for (auto& line : ls){
    lines.push_back(line);
  }
}


SourceContent::~SourceContent() {}


std::vector<Line> SourceContent::getLines() {
  return lines;
}




