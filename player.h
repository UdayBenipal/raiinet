#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <map>
#include <vector>

struct info{
	char type;
	char strength;
	int hidden;
};

class player {
	std::map <char, info> links;
	std::vector <char> abilities;
	int data;
	int virus;
    int total_abilties;
public:
    void init(int player, std::string s, std::string ablts);

    int getdata() const;

    int getvirus() const;

    std::vector<char> get_abilities() const;

    void update(char type);

    void unhide(char key);

    char get_ability(int index);

    void toggle(char key);

    int is_hidden(char key);

    void display_abilities() const;

    void display(std::ostream &out, int player, bool turn);
};

#endif
