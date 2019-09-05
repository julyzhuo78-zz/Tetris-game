#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include "observer.h"
#include <vector>
#include <iostream>

class TextDisplay: public Observer {
  std::vector<std::vector<char>> theDisplay;
  
public:
  TextDisplay();
  void notify(Subject &whoFrom) override;
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif


