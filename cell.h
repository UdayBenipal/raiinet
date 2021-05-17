#ifndef _CELL_H_
#define _CELL_H_
#include <memory>
#include "subject.h"

class Abilities;
class Link;
struct posn;

class Cell : public Subject<posn, std::shared_ptr<Link>>{
	int row, col;
	std::shared_ptr<Link> l_ptr = nullptr;
	bool server_port;
	std::shared_ptr<Abilities> a = nullptr;
public:
	Cell(int row = 0, int col = 0, bool server_port = false);
	void set(std::shared_ptr<Link> ptr);
	posn getInfo() const;
 	std::shared_ptr<Link> getState() const;
 	bool is_server() const;
 	void add_ability(std::shared_ptr<Abilities> ptr);
 	std::shared_ptr<Abilities> get_ability() const;
 	virtual ~Cell() {};
};

#endif
