#ifndef _GRID_H_
#define _GRID_H_
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "cell.h"
#include "block.h"
#include "textdisplay.h"

class GraphicsDisplay;
//class InvalidMove{};
const int defaultlevel = 0;
const int defaultseed = 88;

class Grid {
  std::vector<std::vector<Cell>> theGrid;
  
  std::vector<std::string> file; // default file;
  int fileBlockNo = 0;   // Number of blocks in file
  std::vector<std::string> randomFile; // file read for non-random mode;
  int randomFileBlockNo = 0;  // Number of blocks in randomFile
  
  TextDisplay *td = nullptr;
  GraphicsDisplay *gd = nullptr;
  
  Block *curBlock = nullptr;
  Block *nextBlock = nullptr;
  Block *hintBlock = nullptr;
  
  int curLevel;
  int score = 0;
  int highScore = 0;
  
  int blockCount = 0;  // Total number of blocks being generated
  int randomBlockCount = 0; // No of blocks in random mode
  int clearedRowNo = 0;  // No of rows deleted
  bool random = false;
  
  // check if the game is over
  bool isOver();
  // check if the line is full
  bool isFull(int r);
  // returns the lowest row no which is unfilled
  int findLowAvailable(int row, int col);
  // returns a block pointer
  Block* generateBlock();
  
public:
  Grid(bool needGd, int level = defaultlevel, int seed = defaultseed, std::string scriptfile = "sequence.txt"); // constructor of Grid
  void init(); // initialize the Grid
  
  void setLevel(int level); // set the current level to level
  void levelUp(); // increment the current level by 1
  void levelDown(); // decrement the current level by 1
  int getLevel(); // return the current level

  void left(); // move the current block to the left
  void right(); // move the current block to the right
  bool down(); // move down the current block
  void cw(); // rotate the current block in clockwise direction
  void ccw(); // rotate the current block in anti-clockwise direction
  bool drop(); // drop the current block
  void hint(); // appears the hint block
  
  void eraseHint(); // erase the hint block
  
  void changeBlock(std::string s); // change the current block to the type s
  
  void makeRandom(); // set to random mode
  void setNoRandom(std::string filename); // set to non-random mode and read the
                                          // filename for available blocks
  
  // overload the output operator to print the grid
  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif

