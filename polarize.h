#ifndef _POLARIZE_H_
#define _POLARIZE_H_
#include "abilities.h"

class polarize: public Abilities {
public:
	void apply(Cell &c, player &p) override;
	int get_player() override;
	~polarize() {};
};

#endif
