#ifndef _GRAPHICSDISPLAY_H_
#define _GRAPHICSDISPLAY_H_

#include "observer.h"
#include "window.h"
#include "state.h"
#include "subject.h"

class GraphicsDisplay: public Observer {
  const int BHeight = 450, BWidth = 275;
  const int SWidth = 224, SHeight = 224;
  const int THeight = 49;
  const int Csize = 25;
  Xwindow xw;
  
public:
  GraphicsDisplay(int level);   //constructor
  void notify(Subject &whoNotified) override;
  void drawStatus(int level, int score, int hiScore);
  void drawNext(Colour cl);
};

#endif

