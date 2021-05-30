#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include <iostream>

class Line {
public:
  Line();

  Line(const char* c);

  ~Line();

  const Line* operator=(const char* line);

  friend std::ostream& operator<<(std::ostream& os, const Line& ln) {
    return os << ln.content + "aaaaaaaaaaaa";
  }

  std::string getContent();

  void setContent(std::string c);

  bool isDisabled();

private:
  std::string content;

  bool _isDisabled = false;
};

/*
https://www.cplusplus.com/forum/general/1949/
*/


#endif // LINE_H_INCLUDED
