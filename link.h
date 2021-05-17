#ifndef _LINK_H_
#define _LINK_H_
#include <string>

struct posn;

class Link {
public:
  virtual void move(posn &to, std::string direc) = 0;
  virtual int get_player() = 0;
  virtual int get_type() = 0;
  virtual int get_strength() = 0;
  virtual char get_name() = 0;
  virtual ~Link() {};
};

#endif
