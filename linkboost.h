#ifndef _LINK_BOOST_H_
#define _LINK_BOOST_H_
#include "decorator.h"
#include <string>

class link_boost : public Decorator {
public:
	link_boost(std::shared_ptr<Link> l);
	int get_player() override;
  	int get_type() override;
  	int get_strength() override;
  	char get_name() override;
    void move(posn &to, std::string direc) override;
    ~link_boost() {};
};

#endif
