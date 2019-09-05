#ifndef _SBLOCK_H_
#define _SBLOCK_H_
#include "block.h"
#include "blockImpl.h"

class SBlock : public Block {
  BlockImpl bi;
  
public:
  SBlock(bool heavy = false);
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


