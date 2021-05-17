#include "player.h"
#include <iostream>
#include <sstream>


void player::init(int player, std::string s, std::string ablts) {
	data = 0;
	virus = 0;
	total_abilties = 5;
	char type;
	char strength;

	//stores players name and their info in map
	char c;
	if(player == 1) {
		c = 'a';
	} else {
		c = 'A';
	}
	std::istringstream ss{s};
	for(int i=0; i < 8; ++i) {
		ss >> type;
		ss >> strength;
		links[c+i] = {type, strength, 1};
	}

	//stores players abilities in vector corrsponding to index
	char a;
	std::istringstream sss{ablts};
	while(sss >> a) {
		abilities.emplace_back(a); 
	}
}


int player::getdata() const {
	return data;
}


int player::getvirus() const {
	return virus;
}


void player::update(char type) {
	if (type == 'D') {
		data+=1;
	} else {
		virus+=1;
	}
}


std::vector<char> player::get_abilities() const {
	return abilities;
}


void player::unhide(char key) {
	links[key].hidden = 0;
}


char player::get_ability(int index) {
	char c = abilities.at(index);
	abilities.at(index) += 32;
	if(total_abilties) total_abilties -= 1;
	return c;
}


void player::toggle(char key) {
	if(links[key].type == 'V') {
		links[key].type = 'D';
	} else {
		links[key].type = 'V';
	}
}


int player::is_hidden(char key) {
	return links[key].hidden;
}


void player::display_abilities() const {
	char c;
	for(int i=0; i < 5; ++i) {
		c = abilities.at(i);
		std::cout << i+1 << ":";
		if(c > 96) {
			c -= 32;
			std::cout << c << ":USED    ";
		} else {
			std::cout << c << ":NOT-USED";
		}
		std::cout << "   ";
	}
	std::cout << std::endl;
}


void player::display (std::ostream &out, int player, bool turn) {
	char z;
	if(player == 1) {
		out << "Player 1:" << std::endl;
		z = 'a';
	} else {
		out << "Player 2:" << std::endl;
		z = 'A';
	}

	out << "Downloaded: ";
	out << data << "D, " << virus << "V" << std::endl;
	out << "Abilities: " << total_abilties << std::endl;

	for(int i = 0; i < 8; ++i) {
		out << z << ": ";
		if(turn || !links[z].hidden) {
			out << links[z].type << links[z].strength << "	";
		} else {
			out << "? 	";
		}
		if(i == 3 || i == 7) out << std::endl;
		z+=1;
	}
}
