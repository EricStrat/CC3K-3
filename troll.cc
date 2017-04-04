#include "troll.h"

Troll::Troll() : Player( 120, 120, 25, 25, 15, 15, 0, "Troll" ) {}
Troll::~Troll() {}

void Troll::attack( Human &e )
{
  act = "";
  int dmg = damage( e );
  e.mutHP( -dmg );
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to H (" + hp + " HP)." ;

}

void Troll::attack( Dwarf &e )
{
  act = "";
  int dmg = damage( e );
  e.mutHP( -dmg );
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to W (" + hp + " HP)." ;

}

void Troll::attack( Elf &e )
{
  act = "";
  int dmg = damage( e );
  e.mutHP( -dmg );
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to E (" + hp + " HP)." ;

}

void Troll::attack( Orc  &e )
{
  act = "";
  int dmg = damage( e );
  e.mutHP( -dmg );
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to O (" + hp + " HP)." ;

}

void Troll::attack( Merchant &e )
{ 
  act = "";
  int dmg = damage( e );
  e.mutHP( -dmg );
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to M (" + hp + " HP)." ;
}

void Troll::attack( Dragon &e )
{
  act = "";
  int dmg = damage( e );
  e.mutHP( -dmg );
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to D (" + hp + " HP)." ;
}

void Troll::attack( Halfling &e )
{
  act = "";
  if ( fiftyFifty() )
  {
    int dmg = damage( e );
    e.mutHP( -dmg );
    std::string sdmg = std::to_string(dmg);
    std::string hp = std::to_string(e.getHP());
    act = " PC deals " + sdmg + " to L (" + hp + " HP)." ;
  }
  else 
  {
    std::string hp = std::to_string(e.getHP());
    act = " PC attack missed! L (" + hp + " HP)." ;
  }
}

void Troll::attackedBy( Enemy &e ) { e.attack( * this ); }
