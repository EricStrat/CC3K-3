#ifndef WOUNDATK_H
#define WOUNDATK_H
#include "Potion.h"


class WoundAtk : public Potion {
	public:
	WoundAtk(Player * player);
	std::string getInfo() override;
	~WoundAtk();
        void attack( Human &e ) override;
        void attack( Dwarf &e ) override;
        void attack( Elf &e ) override;
        void attack( Orc &e ) override;
        void attack( Merchant &e ) override;
        void attack( Dragon &e ) override;
        void attack( Halfling &e ) override;
        void attackedBy( Enemy &e ) override;
};

#endif

