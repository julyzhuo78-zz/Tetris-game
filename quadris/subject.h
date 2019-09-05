#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "state.h"
#include "observer.h"

class Subject {
  std::vector<Observer*> observers;
  
public:
  void attach(Observer *ob);
  void notifyObservers();
  virtual State getState() = 0;
};

#endif

