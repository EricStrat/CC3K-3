#include "vampire.h"

Vampire::Vampire() : Player( 50, 50, 25, 25, 25, 25, 0, "Vampire" ) {}
Vampire::~Vampire() {}

void Vampire::mutHP( int i ) 
{
  HP += i;
  if ( HP <= 0 )
  {
    HP = 0;
    slain();
  }
}

void Vampire::attack( Human &e )
{
  int dmg = damage( e );
  e.mutHP( -dmg );
  act = "";
  mutHP( 5 );
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to H (" + hp + " HP)." ;

}

void Vampire::attack( Dwarf &e )
{
  act = "";
  int dmg = damage( e );
  e.mutHP( -dmg );
  mutHP( -5 );
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to W (" + hp + " HP)." ;

}

void Vampire::attack( Elf &e )
{
  act = "";
  int dmg = damage( e );
  e.mutHP( -dmg );
  mutHP( 5 );
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to E (" + hp + " HP)." ;

}

void Vampire::attack( Orc  &e )
{  
  act = "";
  int dmg = damage( e );
  e.mutHP( -dmg );
  mutHP( 5 );
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to O (" + hp + " HP)." ;
}

void Vampire::attack( Merchant &e )
{
  act = "";
  int dmg = damage( e );
  e.mutHP( -dmg );
  mutHP( 5 );
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to M (" + hp + " HP)." ;
}

void Vampire::attack( Dragon &e )
{
  act = "";
  int dmg = damage( e );
  e.mutHP( -dmg );
  mutHP( 5 );
  std::string sdmg = std::to_string(dmg);
  std::string hp = std::to_string(e.getHP());
  act = " PC deals " + sdmg + " to D (" + hp + " HP)." ;
}

void Vampire::attack( Halfling &e )
{
  act = "";
  if ( fiftyFifty() )
  {
    int dmg = damage( e );
    e.mutHP( -dmg );
    mutHP( 5 );
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

void Vampire::attackedBy( Enemy &e ) { e.attack( * this ); }

