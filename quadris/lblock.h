#ifndef _LBLOCK_H_
#define _LBLOCK_H_
#include "block.h"
#include "blockImpl.h"

class LBlock : public Block {
  BlockImpl bi;
  
public:
  LBlock(bool heavy = false);
  BlockImpl getInfo() override;
  void setInfo(BlockImpl& bi) override;
  void left() override;
  void right() override;
  void down() override;
  void cw() override;
  void ccw() override;
  void print() override;
};

#endif


