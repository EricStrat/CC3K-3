#include "Treasure.h"

Treasure::Treasure(Player * player) : Player{player->getHP(), player->getBaseHP(), player->getAtk(), player->getBaseAtk(), player->getDef(), player->getBaseDef(), player->getGold(), player->getRace()}, player{player} {
	treasuretype = "N/A";
}


Treasure::~Treasure() {}
