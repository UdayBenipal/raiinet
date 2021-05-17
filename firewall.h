#ifndef _FIREWALL_H_
#define _FIREWALL_H_
#include "abilities.h"

class firewall: public Abilities {
	int plr;
public:
	firewall(int p);
	int get_player() override;
	void apply(Cell &c, player &p) override;
	virtual ~firewall() {};
};

#endif
