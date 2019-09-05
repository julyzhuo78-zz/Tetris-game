#include "jblock.h"
#include <utility>
#include <iostream>
#include "blockImpl.h"
using namespace std;

JBlock::JBlock(bool heavy) {
  bi.lowerLeftR = 4;
  bi.lowerLeftC = 0;
  bi.len = 3;
  bi.width = 2;
  bi.cl = Colour::Cyan;
  bi.heavy = heavy;
  bi.r[0] = 3;
  bi.c[0] = 0;
  bi.r[1] = 4;
  bi.c[1] = 0;
  bi.r[2] = 4;
  bi.c[2] = 1;
  bi.r[3] = 4;
  bi.c[3] = 2;
}


BlockImpl JBlock::getInfo() {
  return bi;
}


void JBlock::setInfo(BlockImpl& bi){
  this->bi = bi;
}


void JBlock::left() {
  for(int i = 0; i < 4; ++i){
    bi.c[i] -= 1;
  }
  bi.lowerLeftC -= 1;
}


void JBlock::right() {
  for(int i = 0; i < 4; ++i){
    bi.c[i] += 1;
  }
  bi.lowerLeftC += 1;
}


void JBlock::down() {
  for(int i = 0; i < 4; ++i){
    bi.r[i] += 1;
  }
  bi.lowerLeftR += 1;
}


void JBlock::cw() {
  for (int i = 0; i < 4; ++i) {
    int diff_r = bi.r[i] - bi.lowerLeftR;
    int diff_c = bi.c[i] - bi.lowerLeftC;
    bi.r[i] = bi.lowerLeftR + diff_c - (bi.len - 1);
    bi.c[i] = bi.lowerLeftC - diff_r;
  }
  swap(bi.len, bi.width);
}


void JBlock::ccw() {
  for (int i = 0; i < 4; ++i) {
    int diff_r = bi.r[i] - bi.lowerLeftR;
    int diff_c = bi.c[i] - bi.lowerLeftC;
    bi.r[i] = bi.lowerLeftR - diff_c;
    bi.c[i] = bi.lowerLeftC + diff_r + (bi.width - 1);
  }
  swap(bi.len, bi.width);
}


void JBlock::print() {
  cout << "J" << endl;
  cout << "JJJ" << endl;
}
