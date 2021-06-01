#ifndef TWOPASSESASSEMBLER_H_INCLUDED
#define TWOPASSESASSEMBLER_H_INCLUDED

#include "assembler/assembler.h"
#include "assembler/assemblydata.h"
#include "zerothpass.h"
#include "zerothpass2.h"


class TwoPassesAssembler : public Assembler {
public:
  TwoPassesAssembler(AssemblyData* ad) {
    assemblyData = ad;
    zerothPass = ZerothPass(ad);
    zerothPass2 = ZerothPass2(ad);
  }

  void run() {
    zerothPass.run();
    zerothPass2.run();
  }

private:
  AssemblyData* assemblyData;

  ZerothPass zerothPass;

  ZerothPass2 zerothPass2;
};


#endif // TWOPASSESASSEMBLER_H_INCLUDED
