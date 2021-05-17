#ifndef _SCAN_H_
#define _SCAN_H_
#include "abilities.h"

class scan: public Abilities {
public:
	void apply(Cell &c, player &p) override;
	int get_player() override;
	~scan() {};
};

#endif
