#ifndef ZEROTHPASS_H_INCLUDED
#define ZEROTHPASS_H_INCLUDED

#include "assembler/scanner/scanner.h"
#include "assembler/source.h"
#include "assembler/assemblydata.h"
#include "util/util.h"


class ZerothPass {
public:
  ZerothPass();

  ZerothPass(AssemblyData* ad);

  ~ZerothPass();

  void run();

private:
  void runOn(Source* source);

  AssemblyData* assemblyData;
};


#endif // ZEROTHPASS_H_INCLUDED
