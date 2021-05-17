#ifndef _ABILITIES_H_
#define _ABILITIES_H_

struct posn; 
class Cell;
class player;

class Abilities {
public:
	virtual void apply(Cell &c, player &p) = 0;
	virtual int get_player() = 0;
	virtual ~Abilities() {};
};

#endif
