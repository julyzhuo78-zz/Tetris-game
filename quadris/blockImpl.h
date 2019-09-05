#ifndef _BLOCKIMPL_H_
#define _BLOCKIMPL_H_

struct BlockImpl{
  int r[4];
  int c[4];
  int lowerLeftR, lowerLeftC;
  int len, width;
  bool heavy;
  Colour cl;
};

#endif

