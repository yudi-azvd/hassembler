#ifndef ZEROTHPASS2_H_INCLUDED
#define ZEROTHPASS2_H_INCLUDED


#include "assembler/scanner/scanner.h"
#include "assembler/assemblerdata.h"
#include "util/util.h"


class ZerothPass2 {
public:
  ZerothPass2(AssemblyData* ad);

  ~ZerothPass2();

  void run();

private:
  void runOn(Source* source);

  AssemblyData* assemblyData;

};


#endif // ZEROTHPASS2_H_INCLUDED
