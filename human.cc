#include "human.h"

Human::Human() : Enemy( 140, 140, 20, 20, 20, 20, 0, "Human", 'H' ) {}
Human::~Human(){}

void Human::attack( Shade &p )
{
  if ( fiftyFifty() )
  {
    int dmg = damage( p );
    p.mutHP( -dmg );
  }
}

	 
void Human::attack( Drow &p )
{
  if ( fiftyFifty() )
  { 
    int dmg = damage( p );
    p.mutHP( -dmg );
  }
}

void Human::attack( Vampire &p )
{
  if ( fiftyFifty() )
  {
    int dmg = damage( p );
    std::cout << dmg << std::endl;
    p.mutHP( -dmg );
  }
}

void Human::attack( Troll &p )
{
  if ( fiftyFifty() )
  {
    int dmg = damage( p );
    p.mutHP( -dmg );
  }
}


void Human::attack( Goblin &p )
{
  if ( fiftyFifty() )
  {
    int dmg = damage( p );
    p.mutHP( -dmg );
  }
}


void Human::attackedBy( Player &p ) { p.attack( *this ); }
