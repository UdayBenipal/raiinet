#include "firewall.h"
#include "cell.h"
#include "player.h"
#include "link.h"

firewall::firewall(int p): plr{p} {}

int firewall::get_player() {
	return plr;
}

void firewall::apply(Cell &c, player &p) {
	if(c.getState()->get_player() != plr) {
		p.unhide(c.getState()->get_name());
		if(c.getState()->get_type() == 'V') {
			c.set(nullptr);
			p.update('V');
		}
	}
}
