#ifndef _STATE_H
#define _STATE_H

enum class Colour {NoColour, Red, Cyan, Magenta, Yellow, Green, Brown, Blue, Orange, White, Black};

struct State {
  int r, c;
  Colour cl;
};

#endif

