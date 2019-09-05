#include "cell.h"
#include "subject.h"

Cell::Cell(int r, int c, Colour cl): s{r,c,cl} {}

void Cell::setState(State &s) {
  this->s = s;
}


State Cell::getState() {
  return s;
}
