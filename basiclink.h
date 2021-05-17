#ifndef _BASIC_LINK_H_
#define _BASIC_LINK_H_
#include "link.h"
#include <string>

class basic_Link : public Link {
	int player;
	char type;
	int strength;
	char name;   
public:
    basic_Link(int player, char type, int strength, char name);
    int get_player() override;
    int get_type() override;
    int get_strength() override;
    char get_name() override;
    void move(posn &to, std::string direc) override;
    ~basic_Link() {};
};

#endif
