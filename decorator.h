#ifndef DECORATOR_H
#define DECORATOR_H
#include <memory>
#include "link.h"

class Decorator: public Link {
protected:
   std::shared_ptr<Link> l;
public:
  Decorator(std::shared_ptr<Link> l): l{l} {};
  virtual ~Decorator() {};
};

#endif
