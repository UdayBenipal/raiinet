#ifndef _LINK_POLARIZE_
#define _LINK_POLARIZE_
#include "decorator.h"
#include <string>

class link_polarize : public Decorator {
	public:
	link_polarize(std::shared_ptr<Link> l);
	int get_player() override;
  	int get_type() override;
  	int get_strength() override;
  	char get_name() override;
    void move(posn &to, std::string direc) override;
    ~link_polarize() {};
};

#endif
