#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <fstream>

#include "hasm/hasmdata.h"
#include "hasm/hasmexception.h"


class Input {
public:
  Input(HasmData* hasmData);

  ~Input();

  void readFiles();

private:
  void readFile(std::string filename);

  HasmData* hasmData;
};


#endif // INPUT_H_INCLUDED
