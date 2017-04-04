#include "shade.h"

Shade::Shade() : Player( 125, 125, 25, 25, 25, 25, 0, "Shade" ) {} 
Shade::~Shade() {}

int Shade::getScore() { return 1.5 * gold; }

void Shade::attack( Human &e )
{
  int dmg = damage( e );
  e.mutHP( -dmg );
  act = "";
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to H (" + hp + " HP)." ;
}

void Shade::attack( Dwarf &e ) 
{
  int dmg = damage( e );
  e.mutHP( -dmg );
  act.clear();
  act = "";
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to W (" + hp + " HP)." ;
}

void Shade::attack( Elf &e )
{
  int dmg = damage( e );
  e.mutHP( -dmg );
  act.clear();
  act = "";
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to E (" + hp + "HP)." ;
}

void Shade::attack( Orc  &e )
{
  int dmg = damage( e );
  e.mutHP( -dmg );
  act = "";
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to O (" + hp + "HP)." ;
}

void Shade::attack( Merchant &e )
{
  int dmg = damage( e );
  e.mutHP( -dmg );
  act = "";
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to M (" + hp + "HP)." ;
}

void Shade::attack( Dragon &e )
{
  int dmg = damage( e );
  e.mutHP( -dmg );
  act = "";
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to D (" + hp + "HP)." ;
}

void Shade::attack( Halfling &e )
{
  if ( fiftyFifty() )
  {
    int dmg = damage( e );
    e.mutHP( -dmg );
    act = "";
    std::string sdmg = std::to_string(dmg);
    std::string hp = std::to_string(e.getHP());
    act = " PC deals " + sdmg + " to L (" + hp + "HP)." ;
  }
  else 
  {
    act = "";
    std::string hp = std::to_string(e.getHP());
    act = " PC attack missed! L (" + hp + "HP).";
  }
}

void Shade::attackedBy( Enemy &e ) { e.attack( *this ); }

