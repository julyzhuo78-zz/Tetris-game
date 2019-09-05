#ifndef _ZBLOCK_H_
#define _ZBLOCK_H_
#include "block.h"
#include "blockImpl.h"

class ZBlock : public Block {
  BlockImpl bi;
  
public:
  ZBlock(bool heavy = false);
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


