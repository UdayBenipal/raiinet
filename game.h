#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include "cell.h"
#include "player.h"
#include "posn.h"
#include "textdisplay.h"
#include "link.h"
#include "basiclink.h"
#include "subject.h"
#include "observer.h"
#include "abilities.h"
#include "boost.h"
#include "firewall.h"
#include "download.h"
#include "scan.h"
#include "polarize.h"
#include "graphicsdisplay.h"
#include <vector>
#include <string>
#include <memory>
#include <iostream>

class OutofBounds{};
class InvalidPiece{};
class OwnServer{};
class OwnPlayer{};
class InvalidApplication{};

class Game {
	std::vector<std::vector<Cell>> grid;
	std::shared_ptr<player> p1 = nullptr;
	std::shared_ptr<player> p2 = nullptr;
	std::map <char, posn> p1links;
	std::map <char, posn> p2links;
	std::shared_ptr<TextDisplay> td = nullptr;
	std::shared_ptr<GraphicsDisplay> gd = nullptr;
	int turn;
public:
	void init(std::string s1, std::string s2, std::string a1, std::string a2);
	void move(char piece, std::string direc);
	void ability(std::istream &in, int index);
	bool whowon() const;

	void print_abilities() const;

	void add_graphicDisplay();
	void Display() const;

	friend std::ostream &operator<<(std::ostream &out, Game &g);  
};

#endif
