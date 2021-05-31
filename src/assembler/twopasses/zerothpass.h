#ifndef ZEROTHPASS_H_INCLUDED
#define ZEROTHPASS_H_INCLUDED

#include "assembler/scanner/scanner.h"
#include "assembler/source.h"
#include "assembler/assemblerdata.h"
#include "util/util.h"


class ZerothPass {
public:
  ZerothPass();

  ZerothPass(AssemblerData* ad);

  ~ZerothPass();

  void run();

private:
  void runOn(Source* source);

  AssemblerData* assemblerData;
};


#endif // ZEROTHPASS_H_INCLUDED
