#include "linkpolarize.h"

link_polarize::link_polarize(std::shared_ptr<Link> l): Decorator{l} {}

int link_polarize::get_player() {
	return l->get_player();
}

int link_polarize::get_type() {
	if(l->get_type() == 'V') {
		return 'D';
	} else {
		return 'V';
	}
}

int link_polarize::get_strength() {
	return l->get_strength();
}

char link_polarize::get_name() {
	return l->get_name();
}

void link_polarize::move(posn &to, std::string direc) {
	l->move(to, direc);
}
