#include "grid.h"
#include "blockImpl.h"
#include <string>
#include <cstdlib>
#include <iomanip>
#include "iblock.h"
#include "oblock.h"
#include "lblock.h"
#include "tblock.h"
#include "sblock.h"
#include "jblock.h"
#include "zblock.h"
#include "subject.h"
#include "graphicsdisplay.h"
#include "state.h"
using namespace std;

Grid::Grid(bool needGd, int level, int seed, string scriptfile):
file{scriptfile}, td{new TextDisplay{}},
gd{needGd? new GraphicsDisplay{level}: nullptr}, curLevel{level} {
  srand(seed);
  for(int i = 0; i < gridR; ++i) {
    vector<Cell> vc;
    for (int j = 0; j < gridC; ++j) {
      vc.emplace_back(Cell{i, j, Colour::NoColour});
    }
    theGrid.emplace_back(vc);
  }
  
  ifstream tempFile{scriptfile};
  string s;
  tempFile >> s;
  while (tempFile >> s) {
    file.emplace_back(s);
    ++fileBlockNo;
  }
  ++fileBlockNo;
  
  for (int i = 0; i < gridR; ++i) {
    for (int j = 0; j < gridC; ++j) {
      theGrid[i][j].attach(td);
      if(needGd) theGrid[i][j].attach(gd);
        }
  }
}


void Grid::init() {
  score = 0;
  blockCount = 0;
  clearedRowNo = 0;
  randomBlockCount = 0;
  random = false;
  
  // fill in the board with NoColour
  for(int i = 0; i < gridR; ++i) {
    for (int j = 0; j < gridC; ++j) {
      State newState = {i, j, Colour::NoColour};
      theGrid[i][j].setState(newState);
    }
  }
  
  // notify td and gd to do corresponding change
  for(int i = 0; i < gridR; ++i) {
    for (int j = 0; j < gridC; ++j) {
      theGrid[i][j].notifyObservers();
    }
  }
  
  //generate the current block
  curBlock = generateBlock();
  BlockImpl curBi = curBlock->getInfo();
  for (int i = 0; i < 4; ++i){
    State newState = {curBi.r[i], curBi.c[i], curBi.cl};
    (theGrid[curBi.r[i]][curBi.c[i]]).setState(newState);
    theGrid[curBi.r[i]][curBi.c[i]].notifyObservers();
  }
  //generate the next block
  nextBlock = generateBlock();
  
  //init gd
  if (gd) {
    gd->drawStatus(curLevel, score, highScore);
    gd->drawNext(nextBlock->getInfo().cl);
  }
}


void Grid::setLevel(int level) {
  if (level > 4) level = 4;
  curLevel = level;
  if(gd) gd->drawStatus(curLevel, score, highScore);
}


void Grid::levelUp() {
  setLevel(curLevel + 1);
}


void Grid::levelDown() {
  setLevel(curLevel - 1);
}


void Grid::left() {
  BlockImpl bi = curBlock->getInfo();
  // if the block is on the left of the grid
  for(int i = 0; i < 4; ++i) {
    if(bi.c[i] == 0) {
      return;
    }
  }
  
  // first set no colour
  for (int j = 0; j < 4; ++j) {
    State newState = {bi.r[j], bi.c[j], Colour::NoColour};
    (theGrid[bi.r[j]][bi.c[j]]).setState(newState);
  }
  
  // update
  for (int j = 0; j < 4; ++j) {
    theGrid[bi.r[j]][bi.c[j]].notifyObservers();
  }
  
  // check if we can move left
  bool allEmpty = true;
  for (int j = 0; j < 4; ++j) {
    if ((theGrid[bi.r[j]][bi.c[j] - 1]).getState().cl != Colour::NoColour){
      allEmpty = false;
      break;
    }
  }
  
  // we can move, update the status
  if (allEmpty) {
    for (int j = 0; j < 4; ++j) {
      State newState = {bi.r[j], bi.c[j] - 1, bi.cl};
      (theGrid[bi.r[j]][bi.c[j] - 1]).setState(newState);
    }
    
    curBlock->left();
    BlockImpl newBi = curBlock->getInfo();
    
    for (int j = 0; j < 4; ++j) {
      theGrid[newBi.r[j]][newBi.c[j]].notifyObservers();
    }
  } else {// we cannot move, restore to the previous status
    for (int j = 0; j < 4; ++j) {
      State newState = {bi.r[j], bi.c[j], bi.cl};
      (theGrid[bi.r[j]][bi.c[j]]).setState(newState);
    }
    
    for (int j = 0; j < 4; ++j) {
      theGrid[bi.r[j]][bi.c[j]].notifyObservers();
    }
  }
  
  // if the block is heavy, move down
  if (bi.heavy) down();
}


void Grid::right() {
  BlockImpl bi = curBlock->getInfo();
  
  for(int i = 0; i < 4; ++i) {
    if(bi.c[i] == (gridC - 1)){
      return;
    }
  }
  
  for (int j = 0; j < 4; ++j) {
    State newState = {bi.r[j], bi.c[j], Colour::NoColour};
    (theGrid[bi.r[j]][bi.c[j]]).setState(newState);
  }
  
  for (int j = 0; j < 4; ++j) {
    theGrid[bi.r[j]][bi.c[j]].notifyObservers();
  }
  
  bool allEmpty = true;
  for (int k = 0; k < 4; ++k) {
    if ((theGrid[bi.r[k]][bi.c[k] + 1]).getState().cl != Colour::NoColour){
      allEmpty = false;
      break;
    }
  }
  
  if (allEmpty) {
    for (int i = 0; i < 4; ++i) {
      State newState = {bi.r[i], bi.c[i] + 1, bi.cl};
      (theGrid[bi.r[i]][bi.c[i] + 1]).setState(newState);
    }
    for (int j = 0; j < 4; ++j) {
      theGrid[bi.r[j]][bi.c[j] + 1].notifyObservers();
    }
    
    curBlock->right();
    
    BlockImpl newBi = curBlock->getInfo();
    
    for (int j = 0; j < 4; ++j) {
      theGrid[newBi.r[j]][newBi.c[j]].notifyObservers();
    }
  } else {
    for (int i = 0; i < 4; ++i) {
      State newState = {bi.r[i], bi.c[i], bi.cl};
      (theGrid[bi.r[i]][bi.c[i]]).setState(newState);
    }
    
    for (int j = 0; j < 4; ++j) {
      theGrid[bi.r[j]][bi.c[j]].notifyObservers();
    }
  }
  
  if (bi.heavy) down();
}


int Grid::getLevel() {
  return curLevel;
}


bool Grid::down() {
  BlockImpl bi = curBlock->getInfo();
  
  for(int i = 0; i < 4; ++i) {
    if(bi.r[i] == (gridR - 1)) {
      return false;
    }
  }
  
  for (int j = 0; j < 4; ++j) {
    State newState = {bi.r[j], bi.c[j], Colour::NoColour};
    (theGrid[bi.r[j]][bi.c[j]]).setState(newState);
  }
  
  for (int j = 0; j < 4; ++j) {
    theGrid[bi.r[j]][bi.c[j]].notifyObservers();
  }
  
  bool allEmpty = true;
  for (int k = 0; k < 4; ++k) {
    if ((theGrid[bi.r[k] + 1][bi.c[k]]).getState().cl != Colour::NoColour){
      allEmpty = false;
      break;
    }
  }
  
  if (allEmpty) {
    for (int i = 0; i < 4; ++i) {
      State newState = {bi.r[i] + 1, bi.c[i], bi.cl};
      (theGrid[bi.r[i] + 1][bi.c[i]]).setState(newState);
    }

    curBlock->down();
    
    BlockImpl newBi = curBlock->getInfo();
    
    for (int j = 0; j < 4; ++j) {
      theGrid[newBi.r[j]][newBi.c[j]].notifyObservers();
    }
  } else {
    for (int i = 0; i < 4; ++i) {
      State newState = {bi.r[i], bi.c[i], bi.cl};
      (theGrid[bi.r[i]][bi.c[i]]).setState(newState);
    }
    
    for (int j = 0; j < 4; ++j) {
      theGrid[bi.r[j]][bi.c[j]].notifyObservers();
    }
  }
  return allEmpty;
}


void Grid::cw() {
  BlockImpl bi = curBlock->getInfo();
  
  for (int j = 0; j < 4; ++j) {
    State newState = {bi.r[j], bi.c[j], Colour::NoColour};
    (theGrid[bi.r[j]][bi.c[j]]).setState(newState);
  }
  
  for (int j = 0; j < 4; ++j) {
    theGrid[bi.r[j]][bi.c[j]].notifyObservers();
  }
  
  bool canRotate = true;
  for (int i = 0; i < 4; ++i) {
    int diffR = bi.r[i] - bi.lowerLeftR;
    int diffC = bi.c[i] - bi.lowerLeftC;
    int newRow = bi.lowerLeftR + diffC - (bi.len - 1);
    int newCol = bi.lowerLeftC - diffR;
    
    if (newRow < 0 || newRow >= gridR || newCol < 0 || newCol >= gridC){
      canRotate = false;
      break;
    }
    
    if ((theGrid[newRow][newCol]).getState().cl != Colour::NoColour) {
      canRotate = false;
      break;
    }
  }
  
  if (canRotate) {
    for (int i = 0; i < 4; ++i) {
      int diffR = bi.r[i] - bi.lowerLeftR;
      int diffC = bi.c[i] - bi.lowerLeftC;
      int newRow = bi.lowerLeftR + diffC - (bi.len - 1);
      int newCol = bi.lowerLeftC - diffR;
      State newState = {newRow, newCol, bi.cl};
      (theGrid[newRow][newCol]).setState(newState);
    }
    curBlock->cw();
    
    BlockImpl newBi = curBlock->getInfo();
    
    for (int j = 0; j < 4; ++j) {
      theGrid[newBi.r[j]][newBi.c[j]].notifyObservers();
    }
  } else {
    for (int i = 0; i < 4; ++i) {
      State newState = {bi.r[i], bi.c[i], bi.cl};
      (theGrid[bi.r[i]][bi.c[i]]).setState(newState);
    }
    
    for (int j = 0; j < 4; ++j) {
      theGrid[bi.r[j]][bi.c[j]].notifyObservers();
    }
  }
  
  if (bi.heavy) down();
}


void Grid::ccw() {
  BlockImpl bi = curBlock->getInfo();
  
  for (int j = 0; j < 4; ++j) {
    State newState = {bi.r[j], bi.c[j], Colour::NoColour};
    (theGrid[bi.r[j]][bi.c[j]]).setState(newState);
  }
  
  for (int j = 0; j < 4; ++j) {
    theGrid[bi.r[j]][bi.c[j]].notifyObservers();
  }
  
  bool canRotate = true;
  for (int i = 0; i < 4; ++i) {
    int diffR = bi.r[i] - bi.lowerLeftR;
    int diffC = bi.c[i] - bi.lowerLeftC;
    int newRow = bi.lowerLeftR - diffC;
    int newCol = bi.lowerLeftC + diffR + (bi.width - 1);
    
    if (newRow < 0 || newRow >= gridR || newCol < 0 || newCol >= gridC){
      canRotate = false;
      break;
    }
    
    if ((theGrid[newRow][newCol]).getState().cl != Colour::NoColour) {
      canRotate = false;
      break;
    }
  }
  
  if (canRotate) {
    for (int i = 0; i < 4; ++i) {
      int diffR = bi.r[i] - bi.lowerLeftR;
      int diffC = bi.c[i] - bi.lowerLeftC;
      int newRow = bi.lowerLeftR - diffC;
      int newCol = bi.lowerLeftC + diffR + (bi.width - 1);
      State newState = {newRow, newCol, bi.cl};
      (theGrid[newRow][newCol]).setState(newState);
    }
    curBlock->ccw();
    
    BlockImpl newBi = curBlock->getInfo();
    
    for (int j = 0; j < 4; ++j) {
      theGrid[newBi.r[j]][newBi.c[j]].notifyObservers();
    }
  } else {
    for (int i = 0; i < 4; ++i) {
      State newState = {bi.r[i], bi.c[i], bi.cl};
      (theGrid[bi.r[i]][bi.c[i]]).setState(newState);
    }
    
    for (int j = 0; j < 4; ++j) {
      theGrid[bi.r[j]][bi.c[j]].notifyObservers();
    }
  }
  
  if (bi.heavy) down();
}


bool Grid::isFull(int r) {
  for (int i = 0; i < gridC; ++i){
    State s = theGrid[r][i].getState();
    if (s.cl == Colour::NoColour) return false;
  }
  return true;
}


static Block *matchBlock(string c, bool heavy){
  Block *bk;
  if (c == "S") {
    bk = new SBlock(heavy);
  } else if (c == "Z") {
    bk = new ZBlock(heavy);
  } else if (c == "L") {
    bk = new LBlock(heavy);
  } else if (c == "T") {
    bk = new TBlock(heavy);
  } else if (c == "O") {
    bk = new OBlock(heavy);
  } else if (c == "J") {
    bk = new JBlock(heavy);
  } else {// c == "I"
    bk = new IBlock(heavy);
  }
  return bk;
}


Block *Grid::generateBlock() {
  Block *newBlock;
  
  if (curLevel == 0) {// generate the block according to the scriptfile
    newBlock = matchBlock(file[blockCount % fileBlockNo], false);
  } else if (curLevel == 1) {// match the corresponding probability
    const int result = rand() % 12;
    const string reference[] = {"S", "Z", "L", "L", "T", "T",
      "O", "O", "J", "J", "I", "I"};
    newBlock = matchBlock(reference[result], false);
  } else if (curLevel == 2) {// same rules applied as above
    int result = rand() % 7;
    const string reference[] = {"S", "Z", "L", "T", "O", "J", "I"};
    newBlock = matchBlock(reference[result], false);
  } else if ((curLevel >= 3) && random) {// at level 3 and in random mode
    newBlock =  matchBlock(randomFile[randomBlockCount % randomFileBlockNo], true);
    ++randomBlockCount;
    return newBlock;
  } else if (curLevel == 3) {// at level 3 and in non-random mode
    int result = rand() % 9;
    const string reference[] = {"S", "S", "Z", "Z", "L", "T", "O", "J", "I"};
    newBlock = matchBlock(reference[result], true);
  } else {// at level 4
    int result = rand() % 9;
    const string reference[] = {"S", "S", "Z", "Z", "L", "T", "O", "J", "I"};
    newBlock = matchBlock(reference[result], true);
  }
  
  ++blockCount;
  return newBlock;
}


bool Grid::drop() {
  //let the current block keep going down
  while (down()) {}
  
  //clear the full rows if there's any
  BlockImpl bi = curBlock->getInfo();
  int lleft = bi.lowerLeftR;
  int count = 0;
  
  // check width times
  for (int i = bi.width; i > 0; --i) {
    
    //check the lleft-th row is full
    if(isFull(lleft)) {
      ++count;
      
      // move down by one line from lleft-th row
      for (int j = lleft; j > 0; --j) {
        for (int k = 0; k < gridC; ++k) {
          State newState = {j, k, theGrid[j - 1][k].getState().cl};
          theGrid[j][k].setState(newState);
        }
      }
      
      // update the 0th row
      for (int k = 0; k < gridC; ++k) {
        State newState = {0, k, Colour::NoColour};
        theGrid[0][k].setState(newState);
      }
    } else {
      --lleft;
    }
  }
  
  for (int i = 0; i < gridR; ++i) {
    for (int j = 0; j < gridC; ++j) {
      (theGrid[i][j]).notifyObservers();
    }
  }
  
  //update score and highScore
  if (count > 0) {
    score += ((curLevel + count)*(curLevel + count));
    if(score > highScore){
      highScore = score;
    }
    if (gd) gd->drawStatus(curLevel, score, highScore);
  }
  
  //generate next block according to the current level
  if (curLevel == 4) {
    if(blockCount % 5 == 0) {
      if (clearedRowNo == 0) {// if the last five blocks did not clear any row
        const int centre = 5;
        int result = findLowAvailable(0, centre);// find the location to drop
        
        if (result >= 0) {// there is place to drop
          State newState = {result, centre, Colour::Brown};
          theGrid[result][centre].setState(newState);
          theGrid[result][centre].notifyObservers();
          if(isFull(result)) {
            for (int j = result; j > 0; --j) {
              for (int k = 0; k < gridC; ++k) {
                State newState = {j, k, theGrid[j - 1][k].getState().cl};
                theGrid[j][k].setState(newState);
              }
            }
            
            for (int k = 0; k < gridC; ++k) {
              State newState = {0, k, Colour::NoColour};
              theGrid[0][k].setState(newState);
            }
          }
        }
      }
      clearedRowNo = 0; // update the status
    }
  }
  
  // generate new block and update
  delete curBlock;
  curBlock = nextBlock;
  nextBlock = generateBlock();
  
  if (gd) {
    gd->drawNext(nextBlock->getInfo().cl);
  }
  
  //check whether the game is over
  if (!isOver()) {
    BlockImpl bi = curBlock->getInfo();
    
    for (int i = 0; i < 4; ++i){
      State newState = {bi.r[i], bi.c[i], bi.cl};
      (theGrid[bi.r[i]][bi.c[i]]).setState(newState);
      (theGrid[bi.r[i]][bi.c[i]]).notifyObservers();
    }
  } else {
    return false;// game over
  }
  return true;// can continue
}


bool Grid::isOver() {
  BlockImpl bi = curBlock->getInfo();
  
  for (int i = 0; i < 4; ++i) {
    if ((theGrid[bi.r[i]][bi.c[i]]).getState().cl != Colour::NoColour) {
      return true;
    }
  }
  return false;
}


void Grid::changeBlock(string s) {
  // get the state of the current block
  BlockImpl bi = curBlock->getInfo();
  bool heavy = bi.heavy;
  Block *newBlock = matchBlock(s, heavy);
  BlockImpl newBi = newBlock->getInfo();
  
  // set the current block's location to no colour
  for (int i = 0; i < 4; ++i) {
    State newState = {bi.r[i], bi.c[i], Colour::NoColour};
    (theGrid[bi.r[i]][bi.c[i]]).setState(newState);
    (theGrid[bi.r[i]][bi.c[i]]).notifyObservers();
  }
  
  // set the new block's state
  int diffR = bi.lowerLeftR - newBi.lowerLeftR;
  int diffC = bi.lowerLeftC - newBi.lowerLeftC;
  newBi.lowerLeftC = bi.lowerLeftC;
  newBi.lowerLeftR = bi.lowerLeftR;
  
  for (int i = 0; i < 4; ++i) {
    newBi.r[i] += diffR;
    newBi.c[i] += diffC;
  }
  
  // check if we are able to place the new block
  bool allEmpty = true;
  for (int j = 0; j < 4; ++j) {
    if (newBi.lowerLeftC + newBi.len > gridC) {
      allEmpty = false;
      break;
    }
    if(theGrid[newBi.r[j]][newBi.c[j]].getState().cl != Colour::NoColour) {
      allEmpty = false;
      break;
    }
  }
  
  if (allEmpty) {// we can place the new block
    for (int i = 0; i < 4; ++i) {
      State newState = {newBi.r[i], newBi.c[i], newBi.cl};
      theGrid[newBi.r[i]][newBi.c[i]].setState(newState);
      theGrid[newBi.r[i]][newBi.c[i]].notifyObservers();
    }
    newBlock->setInfo(newBi);
    delete curBlock;
    curBlock = newBlock;
  } else {// we cannot place the new block
    for (int i = 0; i < 4; ++i) {
      State newState = {bi.r[i], bi.c[i], bi.cl};
      theGrid[bi.r[i]][bi.c[i]].setState(newState);
      theGrid[bi.r[i]][bi.c[i]].notifyObservers();
    }
  }
}


void Grid::setNoRandom(std::string filename) {
  random = false;
  clearedRowNo = 0;
  randomFile.clear();
  ifstream f{filename};
  string s;
  
  while (f >> s) {
    randomFile.emplace_back(s);
    ++randomFileBlockNo;
  }
}


void Grid::makeRandom() {
  random = true;
}


void Grid::eraseHint() {
  if (hintBlock == nullptr) return;
  
  BlockImpl bi = hintBlock->getInfo();
  for (int i = 0; i < 4; ++i) {
    State newState = {bi.r[i], bi.c[i], Colour::NoColour};
    theGrid[bi.r[i]][bi.c[i]].setState(newState);
    theGrid[bi.r[i]][bi.c[i]].notifyObservers();
  }
  delete hintBlock;
  hintBlock = nullptr;
}


int Grid::findLowAvailable(int row, int col) {
  int result = -1;
  bool allEmpty = true;
  
  for (int i = row; i < gridR; ++i) {
    if (theGrid[i][col].getState().cl != Colour::NoColour) {
      result = i - 1;
      allEmpty = false;
      break;
    }
  }
  
  // if there is a vacant place in the column
  if (result >= row) {
    return result;
  } else if (allEmpty) {
    return gridR - 1;
  } else {// when the column is full
    return -1;
  }
}


static string matchColour(Colour cl) {
  if (cl == Colour::Blue) return "S";
  else if (cl == Colour::Orange) return "Z";
  else if (cl == Colour::Yellow) return "L";
  else if (cl == Colour::Green) return "T";
  else if (cl == Colour::Magenta) return "O";
  else if (cl == Colour::Cyan) return "J";
  else return "I"; // (cl == Colour::Red)
}


void Grid::hint(){
  Colour curCl = curBlock->getInfo().cl;
  bool h = curBlock->getInfo().heavy;
  
  hintBlock = matchBlock(matchColour(curCl), h);
  
  BlockImpl curInfo = curBlock->getInfo();
  int curLowerR = curInfo.lowerLeftR;
  int curLowerC = curInfo.lowerLeftC;
  int len = curInfo.len;
  
  // the rightest available position for current block with its current state
  for (int i = 11 - len; i >= 0; --i) {
    bool allEmpty = true;
    int potentialR = findLowAvailable(curLowerR + 1, i);
    
    // let the hint perfect fit in the best position
    if ((theGrid[curLowerR][curLowerC].getState().cl == Colour::NoColour) &&
        (potentialR != gridR - 1)) {
      ++potentialR;
      if ((theGrid[curLowerR - 1][curLowerC].getState().cl == Colour::NoColour) &&
          (potentialR != gridR - 1)) ++potentialR;
    }
    
    // if the hint appears above the current block
    if (potentialR < curLowerR) continue;
    
    // if the hint appears below the current block
    if (potentialR >= curLowerR) {
      for (int j = 0; j < 4; ++j) {    //check if the current block can fit in
        int r = potentialR - (curLowerR - curInfo.r[j]);
        int c = i + (curInfo.c[j] - curLowerC);
        if (theGrid[r][c].getState().cl != Colour::NoColour) {
          allEmpty = false;
        }
      }
    }
    BlockImpl newInfo = curInfo;
    
    // if there is a hint
    if (allEmpty) {
      for (int j = 0; j < 4; ++j) {
        int r = potentialR - (curLowerR - curInfo.r[j]);
        int c = i + (curInfo.c[j] - curLowerC);
        newInfo.r[j] = r;
        newInfo.c[j] = c;
        State newState = {r, c, Colour::Black};
        theGrid[r][c].setState(newState);
        theGrid[r][c].notifyObservers();
      }
      newInfo.lowerLeftR = potentialR;
      newInfo.lowerLeftC = i;
      hintBlock->setInfo(newInfo); // set the hintBlock
      break;
    }
  }
}


// numDigit(n) checks the number of digits of n
static int numDigit(int n) {
  int result = 1;
  while (n >= 10) {
    ++result;
    n /= 10;
  }
  return result;
}


ostream &operator<<(ostream &out, const Grid &g) {
  int space = numDigit(g.highScore) + 3;
  out << "Level: " << setw(space)  << g.curLevel << endl;
  out << "Score: " << setw(space) << g.score << endl;
  out << "Hi Score: " << g.highScore << endl;
  out << *(g.td);
  out << "Next:" << endl;
  g.nextBlock->print();
  return out;
}
