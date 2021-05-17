#include "game.h"
#include <sstream>


void Game::init(std::string s1, std::string s2, std::string a1, std::string a2) {
	p1 = std::make_shared<player>();
	p2 = std::make_shared<player>();
	p1->init(1, s1, a1);
	p2->init(2, s2, a2);
	turn = 0;
	grid.clear();
	td = std::make_shared<TextDisplay>();

	//stores links of a corresponding to their position 
	for(int i=0; i < 8; ++i) {
		if(i == 3 || i == 4) {
			p1links['a'+i] = {1, i};
		} else {
			p1links['a'+i] = {0, i};
		}
	}
	for(int i=0; i < 8; ++i) {
		if(i == 3 || i == 4) {
			p2links['A'+i] = {6, i};
		} else {
			p2links['A'+i] = {7, i};
		}
	}	

	//set ups the cells and attaches textdisplay as observer
	for(int i = 0; i < 8; ++i) {
		std::vector<Cell> arr;
		for(int j = 0; j < 8; ++j) {
			if((i == 0 || i == 7) && (j == 3 || j == 4)) {
				Cell c = {i,j,true};
				arr.emplace_back(c);
			} else {
				Cell c = {i,j};
				arr.emplace_back(c);
			}
			arr.at(j).attach(td);
		}
		grid.emplace_back(arr);
	}

	//adds links to the initial cells as well as server ports
	char type;
	int strength;
	std::istringstream ss{s1};
	char name = 'a';
	for(int i = 0; i < 8; ++i) {
		ss >> type;
		ss >> strength;
		if(i == 3 || i == 4) {
			(grid.at(1)).at(i).set(std::make_shared<basic_Link>(1, type, strength, name+i));
			(grid.at(1)).at(i).notifyObservers();
		} else {
			(grid.at(0)).at(i).set(std::make_shared<basic_Link>(1, type, strength, name+i));
			(grid.at(0)).at(i).notifyObservers();
		}
	}
	std::istringstream sss{s2};
	name = 'A';
	for(int i = 0; i < 8; ++i) {
		sss >> type;
		sss >> strength;
		if(i == 3 || i == 4) {
			(grid.at(6)).at(i).set(std::make_shared<basic_Link>(2, type, strength, name+i));
			(grid.at(6)).at(i).notifyObservers();
		} else {
			(grid.at(7)).at(i).set(std::make_shared<basic_Link>(2, type, strength, name+i));
			(grid.at(7)).at(i).notifyObservers();
		}
	}
}


void Game::move(char piece, std::string direc) {
	bool player1 = false;
	bool player2 = false;
	posn from, to;

	//gets the piece position that has to be moved
	if(turn) {
		player2 = true;
		if(p2links.find(piece) == p2links.end()) {
			class InvalidPiece ip;                                                                                                                                                                                                                             
			throw ip;
		} else {
			from = p2links[piece];
		}
	} else {
		player1 = true;
		if(p1links.find(piece) == p1links.end()) {
			class InvalidPiece ip;                                                                                                                                                                                                                             
			throw ip;
		} else {
			from = p1links[piece];
		}
	}

	//gets the position where piece has to be moved to
	to = from;
	grid.at(from.row).at(from.col).getState()->move(to, direc);

	//boundary case
	if((player2 && to.row < 0) || (player1 && to.row > 7)) {	
		if(player1) {
			p1->update(grid.at(from.row).at(from.col).getState()->get_type());
			p1->unhide(grid.at(from.row).at(from.col).getState()->get_name());
			p1links.erase(piece);
		}
		else {
			p2->update(grid.at(from.row).at(from.col).getState()->get_type());
			p2->unhide(grid.at(from.row).at(from.col).getState()->get_name());
			p2links.erase(piece);
		}
		grid.at(from.row).at(from.col).set(nullptr);
		grid.at(from.row).at(from.col).notifyObservers();
		turn+=1;
		turn%=2;
		return;
	}

	//outofbound move
	if(to.row < 0 || to.row > 7 || to.col < 0 || to.col > 7) {
		OutofBounds imv;
		throw imv;
	}

	//server port
	if(grid.at(to.row).at(to.col).is_server()) {
		if((player1 && to.row == 7) || (player2 && to.row == 0)) {	
			if(player1) {
				p2->update(grid.at(from.row).at(from.col).getState()->get_type());
				p1->unhide(grid.at(from.row).at(from.col).getState()->get_name());
				p1links.erase(piece);
			}
			else {
				p1->update(grid.at(from.row).at(from.col).getState()->get_type());
				p2->unhide(grid.at(from.row).at(from.col).getState()->get_name());
				p2links.erase(piece);
			}	
			grid.at(from.row).at(from.col).set(nullptr);
			grid.at(from.row).at(from.col).notifyObservers();
			turn+=1;
			turn%=2;
			return;
		} else {
			OwnServer imv;
			throw imv;
		}
	}

	//Battle
	// Checking conditions of Battle and Invalid moves
	if(grid.at(to.row).at(to.col).getState()) {
		if ((player1 && (grid.at(to.row).at(to.col).getState()->get_player() == 2)) ||
			(player2 && (grid.at(to.row).at(to.col).getState()->get_player() == 1))) {
				
				if(player1) {
					p1->unhide(grid.at(from.row).at(from.col).getState()->get_name());
					p2->unhide(grid.at(to.row).at(to.col).getState()->get_name());
				} else {
					p2->unhide(grid.at(from.row).at(from.col).getState()->get_name());
					p1->unhide(grid.at(to.row).at(to.col).getState()->get_name());
				}

				int to_strength = grid.at(to.row).at(to.col).getState()->get_strength();
				int from_strength = grid.at(from.row).at(from.col).getState()->get_strength();
				if (to_strength > from_strength) {
	 				
	 				//download
	 				if(player1) {
						p2->update(grid.at(from.row).at(from.col).getState()->get_type());
						p1links.erase(piece);
					}
					else {
						p1->update(grid.at(from.row).at(from.col).getState()->get_type());
						p2links.erase(piece);
					}

	 				grid.at(from.row).at(from.col).set(nullptr);
					grid.at(from.row).at(from.col).notifyObservers();
					
	 			} else {
	 				//download
	 				if(player1) {
						p1->update(grid.at(to.row).at(to.col).getState()->get_type());
						p1links.erase(piece);
					}
					else {
						p2->update(grid.at(to.row).at(to.col).getState()->get_type());
						p1links.erase(piece);
					}

					grid.at(to.row).at(to.col).set(grid.at(from.row).at(from.col).getState());
					grid.at(from.row).at(from.col).set(nullptr);

					if(player1) {
						p1links[piece] = {to.row, to.col};
					} else {
						p2links[piece] = {to.row, to.col};
					}

					grid.at(to.row).at(to.col).notifyObservers();
					grid.at(from.row).at(from.col).notifyObservers();
				}
		} else if ((player2 && (grid.at(to.row).at(to.col).getState()->get_player() == 2)) ||
				   (player1 && (grid.at(to.row).at(to.col).getState()->get_player() == 1))) {
			OwnPlayer imv;
		 	throw imv;
		}
	} else { //normal move
		grid.at(to.row).at(to.col).set(grid.at(from.row).at(from.col).getState());
		grid.at(from.row).at(from.col).set(nullptr);
		//Updates map
		if(player1) {
			p1links[piece] = {to.row, to.col};
		}
		else {
			p2links[piece] = {to.row, to.col};
		}
		
		grid.at(to.row).at(to.col).notifyObservers();
		grid.at(from.row).at(from.col).notifyObservers();
	}

	//if ability is present on the moved cell
	if(grid.at(to.row).at(to.col).get_ability() != nullptr) {
		if(player1) {
			grid.at(to.row).at(to.col).get_ability()->apply(grid.at(to.row).at(to.col), *p1);
		} else {
			grid.at(to.row).at(to.col).get_ability()->apply(grid.at(to.row).at(to.col), *p2);
		}
		grid.at(to.row).at(to.col).notifyObservers();
	}

	turn+=1;
	turn%=2;
}


void Game::ability(std::istream &in, int index) {
	char abl;
	index-=1;
	if(turn) {
		abl = p2->get_ability(index);
	} else {
		abl = p1->get_ability(index);
	}

	if(abl == 'L') {
		char piece_name;
		posn p;
		in >> piece_name;

		if(turn) {
			if(p2links.find(piece_name) == p2links.end()) {
				class InvalidApplication imv;                                                                                                                                                                                                                             
				throw imv;
			} else {
				p = p2links[piece_name];
			}
		} else {
			if(p1links.find(piece_name) == p1links.end()) {
				class InvalidApplication imv;                                                                                                                                                                                                                             
				throw imv;
			} else {
				p = p1links[piece_name];
			}
		}

		std::shared_ptr<Abilities> a = std::make_shared<Boost>();
		a->apply(grid.at(p.row).at(p.col), *p1);

	} else if(abl == 'F') {
		int row, col;
		in >> row >> col;
		if(grid.at(row).at(col).getState() == nullptr && 
			grid.at(row).at(col).get_ability() == nullptr) {
			grid.at(row).at(col).add_ability(std::make_shared<firewall>(turn+1));
			grid.at(row).at(col).notifyObservers();
		} else {
			InvalidApplication imv;
			throw imv;
		}
	} else if(abl == 'D') {
	 	char piece_name;
		posn p;
		in >> piece_name;

		if(turn) {
			if(p1links.find(piece_name) == p1links.end()) {
				class InvalidApplication imv;                                                                                                                                                                                                                             
				throw imv;
			} else {
				p = p1links[piece_name];
			}
			std::shared_ptr<Abilities> a = std::make_shared<download>();
			a->apply(grid.at(p.row).at(p.col), *p2);
			p1links.erase(piece_name);
			grid.at(p.row).at(p.col).notifyObservers();
		} else {
			if(p2links.find(piece_name) == p2links.end()) {
				class InvalidApplication imv;                                                                                                                                                                                                                             
				throw imv;
			} else {
				p = p2links[piece_name];
			}
			std::shared_ptr<Abilities> a = std::make_shared<download>();
			a->apply(grid.at(p.row).at(p.col), *p1);
			p2links.erase(piece_name);
			grid.at(p.row).at(p.col).notifyObservers();
		}
	} else if(abl == 'S') {
	 	char piece_name;
		posn p;
		in >> piece_name;

	 	if('a' <= piece_name && piece_name <= 'z') {
	 		 if(p1links.find(piece_name) == p1links.end()) {
				class InvalidApplication imv;                                                                                                                                                                                                                             
				throw imv;
			} else {
				p = p1links[piece_name];
			}
	 		 std::shared_ptr<Abilities> a = std::make_shared<scan>();
			 a->apply(grid.at(p.row).at(p.col), *p1);
	 	} else {
	 		if(p2links.find(piece_name) == p2links.end()) {
				class InvalidApplication imv;                                                                                                                                                                                                                             
				throw imv;
			} else {
				p = p2links[piece_name];
			}
	 		std::shared_ptr<Abilities> a = std::make_shared<scan>();
			a->apply(grid.at(p.row).at(p.col), *p2);
	 	}
	} else if(abl == 'P') {
		char piece_name;
		posn p;
		in >> piece_name;

		if('a' <= piece_name && piece_name <= 'z') {
	 		if(p1links.find(piece_name) == p1links.end()) {
				class InvalidApplication imv;                                                                                                                                                                                                                             
				throw imv;
			} else {
				p = p1links[piece_name];
			}
	 		std::shared_ptr<Abilities> a = std::make_shared<polarize>();
			a->apply(grid.at(p.row).at(p.col), *p1);
			grid.at(p.row).at(p.col).notifyObservers();
	 	} else {
	 		if(p2links.find(piece_name) == p2links.end()) {
				class InvalidApplication imv;                                                                                                                                                                                                                             
				throw imv;
			} else {
				p = p2links[piece_name];
			}
	 		std::shared_ptr<Abilities> a = std::make_shared<polarize>();
			a->apply(grid.at(p.row).at(p.col), *p2);
			grid.at(p.row).at(p.col).notifyObservers();
	 	}
	}
}


bool Game::whowon() const {
	if(p1->getdata() > 3 || p2->getvirus() > 3) {
		std::cout << "Player 1 won!" << std::endl;
		return true;
	} else if(p2->getdata() > 3 || p1->getvirus() > 3) {
		std::cout << "Player 2 won!" << std::endl;
		return true;
	}
	return false;
}


void Game::print_abilities() const {
	std::cout << "PLAYER1 :  ";
	p1->display_abilities();
	std::cout << "PLAYER2 :  ";
	p2->display_abilities();
}


void Game::add_graphicDisplay() {
	gd = std::make_shared<GraphicsDisplay>(p1,p2);
	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 8; ++j) {
			grid.at(i).at(j).attach(gd);
			grid.at(i).at(j).notifyObservers();
		}
	}
}

void Game::Display() const {
	gd->display();
}

std::ostream &operator<<(std::ostream &out, Game &g) {
	bool player1 = false;
	bool player2 = false;

	if(g.turn) {
		player2 = true;
	} else {
		player1 = true;
	}

	g.p1->display(out, 1, player1);
	out << *(g.td);
	g.p2->display(out, 2, player2);

	return out;
}

