#include "linkboost.h"
#include "posn.h"

link_boost::link_boost(std::shared_ptr<Link> l): Decorator{l} {}

int link_boost::get_player() {
	return l->get_player();
}

int link_boost::get_type() {
	return l->get_type();
}

int link_boost::get_strength() {
	return l->get_strength();
}

char link_boost::get_name() {
	return l->get_name();
}

void link_boost::move(posn &to, std::string direc) {
	l->move(to, direc);
	if (direc == "up") {
		to = {to.row - 1, to.col};
	} else if (direc == "down") {
		to = {to.row + 1, to.col};
	} else if (direc == "left") {
		to = {to.row, to.col - 1};
	} else if (direc == "right") {
		to = {to.row, to.col + 1};
	}
}
