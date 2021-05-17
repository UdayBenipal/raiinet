#include "basiclink.h"
#include "posn.h"

basic_Link::basic_Link(int player, char type, int strength, char name)
: player{player}, type{type}, strength{strength}, name{name} {}

int basic_Link::get_player() {
	return player;
}

int basic_Link::get_type() {
	return type;
}

int basic_Link::get_strength() {
	return strength;
}

char basic_Link::get_name() {
	return name;
}

void basic_Link::move(posn &to, std::string direc) {
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
