#include "oblock.h"
#include <iostream>
#include "blockImpl.h"
using namespace std;

OBlock::OBlock(bool heavy) {
  bi.lowerLeftR = 4;
  bi.lowerLeftC = 0;
  bi.len = 2;
  bi.width = 2;
  bi.cl = Colour::Magenta;
  bi.heavy = heavy;
  bi.r[0] = 3;
  bi.c[0] = 0;
  bi.r[1] = 3;
  bi.c[1] = 1;
  bi.r[2] = 4;
  bi.c[2] = 0;
  bi.r[3] = 4;
  bi.c[3] = 1;
}


BlockImpl OBlock::getInfo() {
  return bi;
}


void OBlock::setInfo(BlockImpl& bi){
  this->bi = bi;
}


void OBlock::left() {
  for(int i = 0; i < 4; ++i){
    bi.c[i] -= 1;
  }
  bi.lowerLeftC -= 1;
}


void OBlock::right() {
  for(int i = 0; i < 4; ++i){
    bi.c[i] += 1;
  }
  bi.lowerLeftC += 1;
}


void OBlock::down() {
  for(int i = 0; i < 4; ++i){
    bi.r[i] += 1;
  }
  bi.lowerLeftR += 1;
}


void OBlock::cw() {}


void OBlock::ccw() {}


void OBlock::print() {
  cout << "OO" << endl;
  cout << "OO" << endl;
}
