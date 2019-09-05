#ifndef _CELL_H_
#define _CELL_H_
#include "subject.h"
#include "state.h"

class Cell : public Subject {
  State s;
  
public:
  Cell(int r, int c, Colour cl);
  void setState(State &s);
  State getState() override;
};

#endif
