#include "Small.h"

Small::Small(Player * player) : Treasure{player} {
	treasuretype = "Small";
	this->mutGold(1);
}

std::string Small::getInfo() {
	return treasuretype;
}

Small::~Small() {
}

void Small::attack( Human &e ) {}
void Small::attack( Dwarf &e ) {}
void Small::attack( Elf &e ) {}
void Small::attack( Orc &e ) {}
void Small::attack( Merchant &e ) {}
void Small::attack( Dragon &e ) {}
void Small::attack( Halfling &e ) {}
void Small::attackedBy( Enemy &e ) {}
