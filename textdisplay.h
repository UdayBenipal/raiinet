#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include <memory>
#include "observer.h"
#include "subject.h"
#include "link.h"
#include "abilities.h"
#include "posn.h"

class Cell;

class TextDisplay: public Observer <posn, std::shared_ptr<Link>> {
  std::vector<std::vector<char>> display;
 public:
  TextDisplay();

  void notify(Subject<posn, std::shared_ptr<Link>> &whoNotified) override;
    
  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
