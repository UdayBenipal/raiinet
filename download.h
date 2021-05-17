#ifndef _DOWNLOAD_H_
#define _DOWNLOAD_H_
#include "abilities.h"

class download: public Abilities {
public:
	void apply(Cell &c, player &p) override;
	int get_player() override;
	~download() {};
};

#endif
