#include "boost.h"
#include "cell.h"
#include "linkboost.h"

void Boost::apply(Cell &c, player &p) {
	c.set(std::make_shared<link_boost>(c.getState()));
}

int Boost::get_player() {
	return 0;
}
