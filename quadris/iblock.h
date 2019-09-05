#ifndef _IBLOCK_H_
#define _IBLOCK_H_
#include "block.h"
#include "blockImpl.h"

class IBlock : public Block {
  BlockImpl bi;
  
public:
  IBlock(bool heavy = false);
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


