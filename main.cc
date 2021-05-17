#include "game.h"
#include <iostream>
#include <string>
#include <fstream>

void cmd_iterpreter(std::istream &in, Game &g, std::string command, bool graphics) {
	char piece;
	std::string direc;
	int index;
	
	if(command == "move") {
		in >> piece;
       		in >> direc;
		try {
			g.move(piece, direc);
			std::cout << g;
			if(graphics) g.Display();
		} catch(OutofBounds &imv) {
			std::cerr << "PIECE CANNOT BE MOVED OUT OF BOUNDS" << std::endl;
		} catch(InvalidPiece &imv) {
			std::cerr << "PIECE DOES NOT EXIST" << std::endl;
		} catch(OwnServer &imv) {
			std::cerr << "PIECE CANNOT BE MOVED ON ITS OWN SERVER" << std::endl;
		} catch(OwnPlayer &imv) {
			std::cerr << "PIECE CANNOT BE MOVED ON ITS OWN PIECE" << std::endl;
		} catch(...) {
			std::cerr << "INVALID MOVE" << std::endl;
		} 
	} else if(command == "abilities") {
		g.print_abilities();
	} else if(command == "ability") {
		try {
			in >> index;
			g.ability(in, index);
		} catch(...) {
			std::cerr << "INVALID APPLICATION OF ABILITY" << std::endl;
		}	
	} else if(command == "board") {
		std::cout << g;
	}
}

int main(int argc, char* argv[]) {
	Game g;
	std::string command;
	std::string file;
	bool won = false;

	std::string l1order = "V1D4V3V2D3V4D2D1";
	std::string l2order = "V1V2V3V4D1D2D3D4";
	std::string a1order = "LFDSP";
	std::string a2order = "LFDSP";
	bool graphics = false;

	int i = 1;
	std::string flag;
	
	while(i < argc) {
		flag = argv[i];
		if(flag == "-ability1") {
			a1order = argv[i+1];
			i+=2;
		} else if(flag == "-ability2") {
			a2order = argv[i+1];
			i+=2;
		} else if(flag == "-link1") {
			l1order = argv[i+1];
			i+=2;
		} else if(flag == "-link2") {
			l2order = argv[i+1];
			i+=2;
		} else if(flag == "-graphics") {
			graphics = true;
			i+=1;
		} else {
			i+=1;
		}
	}

	g.init(l1order, l2order, a1order, a2order);
	if(graphics) g.add_graphicDisplay();
	
	std::cout << g;
	if(graphics) g.Display();

	while(std::cin >> command) {

		if(command == "sequence") {
			std::cin >> file;
			std::ifstream fin{file};
			
			while(fin >> command) {
				if(command == "quit") break;
				cmd_iterpreter(fin, g, command, graphics);
				if(g.whowon()) {
					won = true;
					break;
				}
			}
			if(won) break;
		} else {
			if(command == "quit") break;
			cmd_iterpreter(std::cin, g, command, graphics);
			if(g.whowon()) break;
		}
	}
}
