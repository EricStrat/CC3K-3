#ifndef TREASURE_H
#define TREASURE_H
#include "player.h"

class Treasure : public Player {
	protected:
	Player * player;
	std::string treasuretype;
	public:
	Treasure(Player * player);
	virtual ~Treasure();
};

#endif
