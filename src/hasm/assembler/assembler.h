#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED


class Assembler {
public:
  virtual void run() = 0;

  virtual ~Assembler() { };
};


#endif // ASSEMBLER_H_INCLUDED
