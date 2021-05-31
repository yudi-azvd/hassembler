#include "line.h"


Line::Line() {}


Line::Line(const char* ln) : content{ln} {}


Line::~Line() {}


const Line* Line::operator=(const char* line) {
  Line* l = new Line(line);
  return l;
}


std::string Line::getContent() {
  return content;
}


void Line::setContent(std::string c) {
  content = c;
}


bool Line::isDisabled() {
  return _isDisabled || content.empty();
}


void Line::disable() {
  _isDisabled = true;
}
