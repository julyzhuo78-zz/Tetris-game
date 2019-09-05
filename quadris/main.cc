#include <iostream>
#include <sstream>
#include "observer.h"
#include "grid.h"
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "state.h"
#include "subject.h"
#include "graphicsdisplay.h"
#include "command.h"
using namespace std;

int main(int argc, char *argv[]) {
  bool needGd = true;
  int level = defaultlevel;
  int seed = defaultseed;
  string scriptfile = "sequence.txt"; // default values for Grid constructor
  
  commandInterpreter(argc, argv, needGd, level, seed, scriptfile);

  Grid g {needGd, level, seed, scriptfile};
  string cmd;
  g.init();
  cout << g;
  
  while (cin >> cmd) {
    //left, right, down, clockwise, counterclockwise, drop, levelup, leveldown,
    //norandom file, random, sequence file, I,J,L, restart, hint
    
    int count = 0;
    int numDigit = 0;
    while (1) {
      char c = cmd[numDigit];
      if (isNum(c)) {
        count = count * 10 + getNum(c);
        ++numDigit;
      } else {
        break;
      }
    }
    
    if (count == 0) ++count;
    
    int length = cmd.length();
    cmd = cmd.substr(numDigit, length - numDigit);
    if (cmd != "hint") {
      g.eraseHint();
    }
    
    if (cmd == "sequence") {
      string fileName;
      cin >> fileName;
      ifstream file{fileName};
      string command;
      while (file >> command) {
        if(!(executeCommand(g, command, g.getLevel()))) return 0;
      }
    } else {
      for (int i = 0; i < count; ++i) {
        if(!(executeCommand(g, cmd, g.getLevel()))) return 0;
      }
    }
  }
}
