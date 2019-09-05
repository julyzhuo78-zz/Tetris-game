#include "command.h"
#include <sstream>
#include <string>
using namespace std;

bool isPrefix(string s, string word) { //check if s is the prefix of word
  int len1 = s.length();
  int len2 = word.length();
  if (len1 > len2) return false;
  for (int i = 0; i < len1; ++i) {
    if (s[i] != word[i]) return false;
  }
  return true;
}


bool isNum(char c) { //check if the c is a number char
  return ((c >= '0') && (c <= '9'));
}


int getNum(char n){ // convert n from type char into int
  return n - '0';
}


bool executeCommand(Grid &g, string cmd, int curLevel) { // execute the command with the correct method
  if (isPrefix(cmd, "left")) {
    g.left();
    cout << g;
  }
  else if (isPrefix(cmd, "right")) {
    g.right();
    cout << g;
  }
  else if (isPrefix(cmd, "down")) {
    if (curLevel >= 3) {
      g.down();
      cout << g;
    }
    g.down();
    cout << g;
  }
  else if (isPrefix(cmd, "clockwise")) {
    g.cw();
    cout << g;
  }
  else if (isPrefix(cmd, "counterclockwise")) {
    g.ccw();
    cout << g;
  }
  else if (isPrefix(cmd,"drop")) {
    if(!(g.drop())) {
      cout << "Game Over! Would you like a new game? (Reply y/n)" << endl;
      char c;
      while (1) {
        cin >> c;
        if (c == 'y') {
          g.init();
          cout << g;
          break;
        } else if (c == 'n') {
          return false;
        } else {
          cout << "Please input y/n" << endl;
        }
      }
    }
    cout << g;
  }
  else if (isPrefix(cmd, "levelup")) { //if cmd == "level", levelup will be called
    g.levelUp();
    cout << g;
  }
  else if (isPrefix(cmd, "leveldown")) {
    g.levelDown();
    cout << g;
  }
  else if (isPrefix(cmd, "norandom")) {
    string file;
    cin >> file;
    g.setNoRandom(file);
  }
  else if (isPrefix(cmd, "random")) {
    g.makeRandom();
  }
  else if (isPrefix(cmd, "hint")) {
    g.hint();
    cout << g;
  }
  else if (cmd == "I" || cmd == "J" || cmd == "L" || cmd == "O"
           || cmd == "S" || cmd == "Z" || cmd == "T") {
    g.changeBlock(cmd);
    cout << g;
  }
  else if (isPrefix(cmd, "restart")) {
    g.init();
    cout << g;
  }
  return true;
}


void commandInterpreter(int argc, char* argv[], bool &needGd, int &level, int &seed, string &scriptfile){
  for (int i = 1; i < argc; ++i) {
    string s = argv[i];
    if (s == "-startlevel") {
      ++i;
      istringstream ss(argv[i]);
      ss >> level;
    } else if (s == "-seed") {
      ++i;
      istringstream ss(argv[i]);
      ss >> seed;
    } else if (s == "-text") {
      needGd = false;
    } else if (s == "-scriptfile"){
      ++i;
      scriptfile = argv[i];
    }
  }// check for command line interface
  
}
