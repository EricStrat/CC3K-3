#include "WoundAtk.h"

WoundAtk::WoundAtk(Player * player) : Potion{player} {
	potiontype = "WA";
        if (this->getType() == "Drow") {
                this->mutAtk(-7.5);
        }
        else {
                this->mutAtk(-5);
        }
}


std::string WoundAtk::getInfo() {
	return potiontype;
}

WoundAtk::~WoundAtk() {
//	delete player;
}

void WoundAtk::attack( Human &e ) {}
void WoundAtk::attack( Dwarf &e ) {}
void WoundAtk::attack( Elf &e ) {}
void WoundAtk::attack( Orc &e ) {}
void WoundAtk::attack( Merchant &e ) {}
void WoundAtk::attack( Dragon &e ) {}
void WoundAtk::attack( Halfling &e ) {}
void WoundAtk::attackedBy( Enemy &e ) {}

