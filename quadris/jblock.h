#ifndef _JBLOCK_H_
#define _JBLOCK_H_
#include "block.h"
#include "blockImpl.h"

class JBlock : public Block {
  BlockImpl bi;
  
public:
  JBlock(bool heavy = false);
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


