#ifndef _OBLOCK_H_
#define _OBLOCK_H_
#include "block.h"
#include "blockImpl.h"

class OBlock : public Block {
  BlockImpl bi;
  
public:
  OBlock(bool heavy = false);
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


