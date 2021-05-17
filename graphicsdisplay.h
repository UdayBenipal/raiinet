#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <vector>
#include <map>
#include <memory>
#include <string>
#include "window.h"
#include "observer.h"
#include "subject.h"
#include "link.h"
#include "abilities.h"
#include "posn.h"

class Cell;
class player;

const int white = 0;
const int black = 1;
const int red = 2;
const int green = 3;
const int blue = 4;
const int cyan = 5;
const int yellow = 6;

struct information {
	int colour;
	char name;
	int player;
	char type;
	int strength;
	information(int colour = 0, char name = 0, char player = 0, char type = 0, char strength = 0)
	: colour{colour}, name{name}, player{player}, type{type}, strength{strength} {}
};

class GraphicsDisplay: public Observer<posn, std::shared_ptr<Link>> {
	std::vector<std::map<int,information>> link;
	std::shared_ptr<player> p1 = nullptr;
	std::shared_ptr<player> p2 = nullptr;
	std::shared_ptr<Xwindow> Xw = nullptr;
	int turn;
public:
	GraphicsDisplay(std::shared_ptr<player> p1, std::shared_ptr<player> p2);
	void notify(Subject<posn, std::shared_ptr<Link>> &whoNotified) override;
	void display();
	~GraphicsDisplay() {};
};

#endif
