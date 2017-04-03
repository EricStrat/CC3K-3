#ifndef SMALL_H
#define SMALL_H
#include "Treasure.h"

class Small : public Treasure {
	public:
	Small(Player * player);
	std::string getInfo() override;
	~Small();
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
