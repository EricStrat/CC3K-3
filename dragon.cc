#include "dragon.h"

Dragon::Dragon() : Enemy( 150, 150, 30, 30, 25, 25, 0, "Dragon", 'D' ) {}
Dragon::~Dragon() {}

void Dragon::attack( Shade &p )
{
  std::cout << "Draogn Attacks Shade" << std::endl;
  if ( fiftyFifty() )
  { 
    int dmg = damage( p );
    p.mutHP( -dmg );
  }
}

void Dragon::attack( Drow &p )
{
  std::cout << "Dragon Attacks Drow" << std::endl;
  if ( fiftyFifty() )
  { 
    int dmg = damage( p );
    p.mutHP( -dmg );
  }
}

void Dragon::attack( Vampire &p )
{
  std::cout << "Draogn Attacks Vampire" << std::endl;
  if ( fiftyFifty() )
  { 
    int dmg = damage( p );
    p.mutHP( -dmg );
  }
}

void Dragon::attack( Troll &p )
{
  std::cout << "Dragon Attacks Troll" << std::endl;
  if ( fiftyFifty() )
  { 
    int dmg = damage( p );
    p.mutHP( -dmg );
  }
}

void Dragon::attack( Goblin &p )
{
  std::cout << "Dragon Attacks Drow" << std::endl;
  if ( fiftyFifty() )
  { 
    int dmg = damage( p );
    p.mutHP( -dmg );
  }
}

void Dragon::attackedBy( Player &p ) { p.attack( *this ); }

