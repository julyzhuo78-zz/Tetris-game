#include "sblock.h"
#include <utility>
#include <iostream>
#include "blockImpl.h"
using namespace std;

SBlock::SBlock(bool heavy) {
  bi.lowerLeftR = 4;
  bi.lowerLeftC = 0;
  bi.len = 3;
  bi.width = 2;
  bi.cl = Colour::Blue;
  bi.heavy = heavy;
  bi.r[0] = 3;
  bi.c[0] = 1;
  bi.r[1] = 3;
  bi.c[1] = 2;
  bi.r[2] = 4;
  bi.c[2] = 0;
  bi.r[3] = 4;
  bi.c[3] = 1;
}


BlockImpl SBlock::getInfo() {
  return bi;
}


void SBlock::setInfo(BlockImpl& bi){
  this->bi = bi;
}


void SBlock::left() {
  for(int i = 0; i < 4; ++i){
    bi.c[i] -= 1;
  }
  bi.lowerLeftC -= 1;
}


void SBlock::right() {
  for(int i = 0; i < 4; ++i){
    bi.c[i] += 1;
  }
  bi.lowerLeftC += 1;
}


void SBlock::down() {
  for(int i = 0; i < 4; ++i){
    bi.r[i] += 1;
  }
  bi.lowerLeftR += 1;
}


void SBlock::cw() {
  for (int i = 0; i < 4; ++i) {
    int diff_r = bi.r[i] - bi.lowerLeftR;
    int diff_c = bi.c[i] - bi.lowerLeftC;
    bi.r[i] = bi.lowerLeftR + diff_c - (bi.len - 1);
    bi.c[i] = bi.lowerLeftC - diff_r;
  }
  swap(bi.len, bi.width);
}


void SBlock::ccw() {
  for (int i = 0; i < 4; ++i) {
    int diff_r = bi.r[i] - bi.lowerLeftR;
    int diff_c = bi.c[i] - bi.lowerLeftC;
    bi.r[i] = bi.lowerLeftR - diff_c;
    bi.c[i] = bi.lowerLeftC + diff_r + (bi.width - 1);
  }
  swap(bi.len, bi.width);
}


void SBlock::print(){
  cout << " SS" << endl;
  cout << "SS" << endl;
}
