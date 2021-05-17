#ifndef _BOOST_H_
#define _BOOST_H_
#include "abilities.h"

class Boost: public Abilities {
public:
	void apply(Cell &c, player &p) override;
	int get_player() override;
	~Boost() {};
};

#endif
