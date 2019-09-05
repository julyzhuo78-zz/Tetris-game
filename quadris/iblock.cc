#include "iblock.h"
#include <utility>
#include "blockImpl.h"
#include <iostream>
using namespace std;

IBlock::IBlock(bool heavy) {
  bi.lowerLeftR = 3;
  bi.lowerLeftC = 0;
  bi.len = 4;
  bi.width = 1;
  bi.cl = Colour::Red;
  bi.heavy = heavy;
  bi.r[0] = 3;
  bi.c[0] = 0;
  bi.r[1] = 3;
  bi.c[1] = 1;
  bi.r[2] = 3;
  bi.c[2] = 2;
  bi.r[3] = 3;
  bi.c[3] = 3;
}


BlockImpl IBlock::getInfo() {
  return bi;
}


void IBlock::setInfo(BlockImpl& bi){
  this->bi = bi;
}


void IBlock::left() {
  for(int i = 0; i < 4; ++i){
    bi.c[i] -= 1;
  }
  bi.lowerLeftC -= 1;
}


void IBlock::right() {
  for(int i = 0; i < 4; ++i){
    bi.c[i] += 1;
  }
  bi.lowerLeftC += 1;
}


void IBlock::down() {
  for(int i = 0; i < 4; ++i){
    bi.r[i] += 1;
  }
  bi.lowerLeftR += 1;
}


void IBlock::cw() {
  for (int i = 0; i < 4; ++i) {
    int diff_r = bi.r[i] - bi.lowerLeftR;
    int diff_c = bi.c[i] - bi.lowerLeftC;
    bi.r[i] = bi.lowerLeftR + diff_c - (bi.len - 1);
    bi.c[i] = bi.lowerLeftC - diff_r;
  }
  swap(bi.len, bi.width);
}


void IBlock::ccw() {
  for (int i = 0; i < 4; ++i) {
    int diff_r = bi.r[i] - bi.lowerLeftR;
    int diff_c = bi.c[i] - bi.lowerLeftC;
    bi.r[i] = bi.lowerLeftR - diff_c;
    bi.c[i] = bi.lowerLeftC + diff_r + (bi.width - 1);
  }
  swap(bi.len, bi.width);
}


void IBlock::print() {
  cout << "IIII" << endl;
}
