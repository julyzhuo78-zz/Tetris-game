#ifndef _TBLOCK_H_
#define _TBLOCK_H_
#include "block.h"
#include "blockImpl.h"

class TBlock : public Block {
  BlockImpl bi;
  
public:
  TBlock(bool heavy = false);
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


