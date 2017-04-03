#include "merchant.h"

int Merchant::agro = false;

Merchant::Merchant() : Enemy( 30, 30, 70, 70, 25, 25, 0, "Merchant", 'M' ) {}
Merchant::~Merchant() {}

void Merchant::attack( Shade &p )
{
  if (Merchant::agro)
  { 
    if ( fiftyFifty() )
    {
      int dmg = damage( p );
      std::cout << dmg << std::endl;
      p.mutHP( -dmg );
      std::cout << p.getHP() << std::endl;
    }
  }
}

void Merchant::attack( Drow &p )
{
  if ( Merchant::agro )
  {
    if ( fiftyFifty() )
    {
      int dmg = damage( p );
      std::cout << dmg << std::endl;
      p.mutHP( -dmg );
      std::cout << p.getHP() << std::endl;
    }
  }
}

void Merchant::attack( Vampire &p )
{
  if ( Merchant::agro )
  {
    if ( fiftyFifty() )
    {
      int dmg = damage( p );
      std::cout << dmg << std::endl;
      p.mutHP( -dmg );
      std::cout << p.getHP() << std::endl;
    }
  }
}

void Merchant::attack( Troll &p )
{ 
  if ( Merchant::agro )
  {
    if ( fiftyFifty() )
    {
      int dmg = damage( p );
      std::cout << dmg << std::endl;
      p.mutHP( -dmg );
      std::cout << p.getHP() << std::endl;
    }
  }
}

void Merchant::attack( Goblin &p )
{
  if ( Merchant::agro )
  {
    if ( fiftyFifty() )
    {
      int dmg = damage( p );
      std::cout << dmg << std::endl;
      p.mutHP( -dmg );
    }
  }
}

void Merchant::attackedBy( Player &p ) 
{ 
  Merchant::agro = true;
  p.attack( *this ); 
}

