#ifndef FIRSTPASS_H_INCLUDED
#define FIRSTPASS_H_INCLUDED


class Pass {
public:
  virtual void run() = 0;

  virtual ~Pass() {};

private:
};


#endif // FIRSTPASS_H_INCLUDED
