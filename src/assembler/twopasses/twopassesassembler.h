#ifndef TWOPASSESASSEMBLER_H_INCLUDED
#define TWOPASSESASSEMBLER_H_INCLUDED

#include "assembler/assemblerdata.h"
#include "assembler/twopasses/zerothpass.h"

class TwoPassesAssembler {
public:
  TwoPassesAssembler(AssemblerData* ad) {
    assemblerData = ad;
    zerothPass = ZerothPass(ad);
  }

  void run() {
    for (auto source : assemblerData->getSources()) {
      zerothPass = ZerothPass(assemblerData);
      zerothPass.run();
    }

  }

private:
  AssemblerData* assemblerData;

  ZerothPass zerothPass;
};

#endif // !TWOPASSESASSEMBLER_H_INCLUDED
