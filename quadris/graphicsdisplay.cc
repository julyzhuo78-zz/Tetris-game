#include "graphicsdisplay.h"
#include "state.h"
#include <string>
#include "subject.h"
using namespace std;


GraphicsDisplay::GraphicsDisplay(int level) {
  //add title here
  xw.fillRectangle(0, 0, 500, THeight, 1);
  //add partition
  xw.fillRectangle(0, THeight, 500, 1, 0);
  // Grid
  xw.fillRectangle(0, 50, BWidth, BHeight, 1);
  //add partition
  xw.fillRectangle(BWidth, 50, 1, BHeight, 0);
  // Status
  xw.fillRectangle(276, 50, SWidth, SHeight, 1);
  //add partition
  xw.fillRectangle(276, 274, SWidth, 1, 0);
  // Next
  xw.fillRectangle(276, 275, SWidth, 225, 1);
  
  //add text
  xw.drawString(200, 24, "QUADRIS");
  xw.drawString(300, 65, "Level:      "+ to_string(level));
  xw.drawString(300, 139, "Score:      0");
  xw.drawString(300, 213, "Hi Score:   0");
  
  xw.drawString(300, 290, "Next Block:");
}


void GraphicsDisplay::notify(Subject &whoNotified) {
  State s = whoNotified.getState();
  Colour c = s.cl;
  int row = s.r;
  int col = s.c;
  if (c == Colour::Black) {
    xw.fillRectangle(0 + col*Csize, 50 + row*Csize, Csize, Csize, 0);
  } else if (c == Colour::NoColour) {
    xw.fillRectangle(0 + col*Csize, 50 + row*Csize, Csize, Csize, 1);
  } else if (c == Colour::Red) {
    xw.fillRectangle(0 + col*Csize, 50 + row*Csize, Csize, Csize, 2);
  } else if (c == Colour::Green){
    xw.fillRectangle(0 + col*Csize, 50 + row*Csize, Csize, Csize, 3);
  } else if (c == Colour::Blue) {
    xw.fillRectangle(0 + col*Csize, 50 + row*Csize, Csize, Csize, 4);
  } else if (c == Colour::Cyan) {
    xw.fillRectangle(0 + col*Csize, 50 + row*Csize, Csize, Csize, 6);
  } else if (c == Colour::Yellow) {
    xw.fillRectangle(0 + col*Csize, 50 + row*Csize, Csize, Csize, 5);
  } else if (c == Colour::Magenta) {
    xw.fillRectangle(0 + col*Csize, 50 + row*Csize, Csize, Csize, 7);
  } else if (c == Colour::Orange) {
    xw.fillRectangle(0 + col*Csize, 50 + row*Csize, Csize, Csize, 8);
  } else {
    xw.fillRectangle(0 + col*Csize, 50 + row*Csize, Csize, Csize, 9);
  }
}


void GraphicsDisplay::drawStatus(int level, int score, int hiScore){
  xw.fillRectangle(276, 50, SWidth, SHeight, 1);
  xw.drawString(300, 65, "Level: " + to_string(level));
  xw.drawString(300, 139, "Score: " + to_string(score));
  xw.drawString(300, 213, "Hi Score: " + to_string(hiScore));
}


void GraphicsDisplay::drawNext(Colour c){
  xw.fillRectangle(276, 275, SWidth, 225, 1);
  xw.drawString(300, 290, "Next Block:");
  
  if (c == Colour::Red) {
    xw.fillRectangle(338, 390, 100, 25, 2);
  } else if (c == Colour::Green){
    xw.fillRectangle(351, 375, 75, 25, 3);
    xw.fillRectangle(376, 400, 25, 25, 3);
  } else if (c == Colour::Blue) {
    xw.fillRectangle(376, 375, 50, 25, 4);
    xw.fillRectangle(351, 400, 50, 25, 4);
  } else if (c == Colour::Yellow) {
    xw.fillRectangle(401, 375, 25, 25, 5);
    xw.fillRectangle(351, 400, 75, 25, 5);
  } else if (c == Colour::Cyan) {
    xw.fillRectangle(351, 375, 25, 25, 6);
    xw.fillRectangle(351, 400, 75, 25, 6);
  } else if (c == Colour::Magenta) {
    xw.fillRectangle(363, 375, 50, 50, 7);
  } else { // Orange
    xw.fillRectangle(351, 375, 50, 25, 8);
    xw.fillRectangle(376, 400, 50, 25, 8);
  }
}
