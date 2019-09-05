#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "grid.h"
#include <string>
#include <iostream>

bool isPrefix(std::string s, std::string word);

bool isNum(char c);

int getNum(char n);

bool executeCommand(Grid &g, std::string cmd, int curLevel);

void commandInterpreter(int argc, char* argv[], bool &needGd, int &level, int &seed, std::string &scriptfile);

#endif
