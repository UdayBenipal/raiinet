#include "scan.h"
#include "cell.h"
#include "player.h"
#include "link.h"

void scan::apply(Cell &c, player &p) {
	p.unhide(c.getState()->get_name());
}

int scan::get_player() {
	return 0;
}
