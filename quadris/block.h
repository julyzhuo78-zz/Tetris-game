#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "state.h"
#include "blockImpl.h"

const int gridR = 18, gridC = 11, startR = 3;

class Block {
public:
  virtual BlockImpl getInfo() = 0;
  virtual void setInfo(BlockImpl& bi) = 0;
  virtual void left() = 0;
  virtual void right() = 0;
  virtual void down() = 0;
  virtual void cw() = 0; // clockwise
  virtual void ccw() = 0; // counterclockwise
  virtual void print() = 0;
  virtual ~Block();
};

#endif
