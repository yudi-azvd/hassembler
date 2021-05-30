#ifndef ZEROTHPASS_H_INCLUDED
#define ZEROTHPASS_H_INCLUDED

#include "hasm/hasmdata.h"
#include "assembler/scanner/scanner.h"
#include "util/util.h"


class ZerothPass {
public:
  ZerothPass(Source& s);

  ~ZerothPass();

  void run();

private:
  Source& source;
};


#endif // ZEROTHPASS_H_INCLUDED
