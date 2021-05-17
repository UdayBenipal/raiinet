#include "cell.h"
#include "posn.h"

Cell::Cell(int row, int col, bool server_port) : row{row}, col{col}, server_port{server_port} {}

void Cell::set(std::shared_ptr<Link> ptr) {
	l_ptr = ptr;
}

std::shared_ptr<Link> Cell::getState() const {
	return l_ptr;
}

posn Cell::getInfo() const {
	posn p;
	p.row = row;
	p.col = col;
	return p;
}

bool Cell::is_server() const {
	return server_port;
}

void Cell::add_ability(std::shared_ptr<Abilities> ptr) {
	a = ptr;
}

std::shared_ptr<Abilities> Cell::get_ability() const {
	return a;
}
