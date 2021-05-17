#include "polarize.h"
#include "linkpolarize.h"
#include "cell.h"
#include "player.h"
#include "link.h"

void polarize::apply(Cell &c, player &p) {
	c.set(std::make_shared<link_polarize>(c.getState()));
	p.toggle(c.getState()->get_name());
}

int polarize::get_player() {
	return 0;
}
