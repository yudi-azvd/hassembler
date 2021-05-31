#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include <iostream>

class Line {
public:
  Line();

  Line(const char* ln);

  ~Line();

  const Line* operator=(const char* line);

  friend std::ostream& operator<<(std::ostream& os, const Line& ln) {
    return os << (ln._isDisabled ? "- " : "+ ") << ln.content;
  }

  std::string getContent();

  void setContent(std::string c);

  bool isDisabled();

  void disable();

private:
  std::string content;

  bool _isDisabled = false;
};

/*
https://www.cplusplus.com/forum/general/1949/
*/


#endif // LINE_H_INCLUDED
