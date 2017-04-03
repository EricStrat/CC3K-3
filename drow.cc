#include "drow.h"

Drow::Drow() : Player( 150, 150, 25, 25, 15, 15, 0, "Drow" ) {}
Drow::~Drow() {}

void Drow::attack( Human &e )
{
  int dmg = damage( e );
  e.mutHP( -dmg );
}

void Drow::attack( Dwarf &e )
{
  int dmg = damage( e );
  std::cout << dmg << std::endl;
}

void Drow::attack( Elf &e )
{
  int dmg = damage( e );
  e.mutHP( -dmg );
}

void Drow::attack( Orc  &e )
{
  int dmg = damage( e );
  e.mutHP( -dmg );
}

void Drow::attack( Merchant &e )
{
  int dmg = damage( e );
  e.mutHP( -dmg );
}

void Drow::attack( Dragon &e )
{
  int dmg = damage( e );
  e.mutHP( -dmg );
}

void Drow::attack( Halfling &e )
{
  if ( fiftyFifty() )
  {
    int dmg = damage( e );
    e.mutHP( -dmg );
    std::cout << e.getHP() << std::endl;
  }
}

void Drow::attackedBy( Enemy &e ) { e.attack( * this ); }
