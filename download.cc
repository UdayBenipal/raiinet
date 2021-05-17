#include "download.h"
#include "cell.h"
#include "player.h"
#include "link.h"

void download::apply(Cell &c, player &p) {
	p.update(c.getState()->get_type());
	c.set(nullptr);
}

int download::get_player() {
	return 0;
}
