#include "textdisplay.h"
#include <iostream>
#include "state.h"
#include "subject.h"
using namespace std;

const int gridR = 18;
const int gridC = 11;

TextDisplay::TextDisplay() {
  for(int i = 0; i < gridR; ++i) {
    vector<char> vc;
    for (int j = 0; j < gridC; ++j) {
      vc.emplace_back(' ');
    }
    theDisplay.emplace_back(vc);
  }
}


char matchCl(Colour cl){
  if (cl == Colour::NoColour) {
    return ' ';
  } else if (cl == Colour::Red) {
    return 'I';
  } else if (cl == Colour::Cyan) {
    return 'J';
  } else if (cl == Colour::Magenta) {
    return 'O';
  } else if (cl == Colour::Yellow) {
    return 'L';
  } else if (cl == Colour::Green) {
    return 'T';
  } else if (cl == Colour::Blue) {
    return 'S';
  } else if (cl == Colour::Orange) {
    return 'Z';
  } else if (cl == Colour::Brown) {
    return '*';
  } else {
    return '?';
  }
}


void TextDisplay::notify(Subject &whoFrom) {
  State s = whoFrom.getState();
  theDisplay[s.r][s.c] = matchCl(s.cl);
}


ostream &operator<<(ostream &out, const TextDisplay &td) {
  for (int i = 0; i < gridC; ++i) {
    out << "-";
  }
  out << endl;
  for (int i = 0; i < gridR; ++i) {
    for (int j = 0; j < gridC; ++j) {
      out << td.theDisplay[i][j];
    }
    out << endl;
  }
  for (int i = 0; i < gridC; ++i) {
    out << "-";
  }
  out << endl;
  return out;
}
