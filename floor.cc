#include "floor.h"
#include "subscriptions.h"
#include "subject.h"
#include "shade.h"
#include "ctime"
#include <stdexcept>
Floor::Floor( int level, std::string cmd ) 
: level{level}, len{len}, wid{wid}
{
  if ( cmd == "s" || cmd == "S" ) mainChar = new Shade;
  else if ( cmd == "d" || cmd == "D" ) mainChar = new Drow;
  else if ( cmd == "v" || cmd == "V" ) mainChar = new Vampire;
  else if ( cmd == "g" || cmd == "G" ) mainChar = new Goblin;
  else if ( cmd == "t" || cmd == "T" ) mainChar = new Troll;
}

Player* Floor::getMainChar(){ return mainChar; }

void Floor::clearFloor() 
{ 
  theFloor.clear(); 
  theChambers.clear();// leak mem??
  theEnemies.clear(); // leak mem??
}

Floor::~Floor() { clearFloor(); }


void Floor::init() 
{ 
	if ( theFloor.size() ) clearFloor();

	// make vectors

	for ( int i = 0; i < 5; ++i )
	{
		Chamber* ch = new Chamber;
		theChambers.emplace_back( ch );
	}    
	srand( time(NULL) );
	for ( int i = 0; i < 20; ++i ) 
	{
		int rng = rand() % 18; 
		if ( rng < 4 ) 
		{
			Human* ene = new Human;
			theEnemies.emplace_back( ene );
		}
		else if ( rng < 7 )
		{
			Dwarf* ene = new Dwarf;
			theEnemies.emplace_back( ene );
		}
		else if ( rng < 12 ) 
		{
			Halfling* ene = new Halfling;
			theEnemies.emplace_back( ene );
		}
		else if ( rng < 14 )
		{
			Elf* ene = new Elf;
			theEnemies.emplace_back( ene );
		}
		else if ( rng < 16 )
		{
			Orc* ene = new Orc;
			theEnemies.emplace_back( ene );
		}
		else 
		{
			Merchant* ene = new Merchant;
			theEnemies.emplace_back( ene );
		}
	}

	std::ifstream file("stage.txt");
	int row = 0;
	int col = 0;
	char cha;
	while ( file.get(cha) ) 
	{
		if (col == 0 ) 
		{
			theFloor.emplace_back();
		}
		if ( col >= 0 && col < 80 )
		{
			Cell *cell = new Cell( cha, row, col ); // leak mem?
			theFloor[row].emplace_back( cell );
			if ( cha == 'A' ) theChambers.at( 0 )->theChamber.emplace_back( cell );
			else if ( cha == 'B' ) theChambers.at( 1 )->theChamber.emplace_back( cell ); 
			else if ( cha == 'C' ) theChambers.at( 2 )->theChamber.emplace_back( cell );
			else if ( cha == 'D' ) theChambers.at( 3 )->theChamber.emplace_back( cell );
			else if ( cha == 'E' ) theChambers.at( 4 )->theChamber.emplace_back( cell ); 
			if ( row != 0 && col != 0 ) 
			{
				cell->link( theFloor[row-1][col] ); // link to the left
				cell->link( theFloor[row-1][col-1] ); // link up left
				cell->link( theFloor[row][col-1] ); // link up
			}
			else if ( row != 0 ) cell->link( theFloor[row-1][col] ); 
			else if ( col != 0 ) cell->link( theFloor[row][col-1] );
			if ( row != 0 && col != 79 ) cell->link( theFloor[row-1][col+1] );
			++col;
		}
		if ( col == 80 )
		{
			col = 0;
			++row;
		}
	}
	srand( time(NULL) );
	int charChamb = rand() % 5;
	theChambers.at( charChamb )->placeChar( mainChar );
	for ( int i = 0; i < 20; ++i )
	{
		int z = rand() % 5;
		theChambers.at( z )->placeChar( theEnemies.at( i ) );
	}
	// place stair not in chamber q
	while ( true )
	{
		int cham = rand() % 5;
		if ( cham != charChamb ) 
		{
			int pos = rand() % (theChambers.at( cham )->theChamber.size());
			theChambers.at( cham )->theChamber.at( pos )->setStair();
			break;
		}
	}
	// place potions;
	srand( time(NULL) );
	for ( int i = 0; i < 10; ++i )
	{
		int cham = rand() % 5;
		int pos = rand() % ( theChambers.at( cham )->theChamber.size() );
		theChambers.at( cham )->theChamber.at( pos )->setPotion();
		theChambers.at( cham )->remove( pos); 
	}
	srand( time(NULL) );
	//place treasures
	for ( int i = 0; i < 10; ++i )
	{
		int cham = rand() % 5;
		int pos = rand() % ( theChambers.at( cham )->theChamber.size() );
		int tr = rand() % 8;
		if ( tr < 2 ) theChambers.at( cham )->theChamber.at( pos )->setTreasure( "small" );
		else if ( tr < 7 ) theChambers.at( cham )->theChamber.at( pos )->setTreasure( "normal" );
		else 
		{ 
			Dragon* dra = new Dragon;
			theChambers.at( cham )->theChamber.at( pos )->setTreasure( "dragon" );
			int dpos;
			while(true)
			{
				int r = theChambers.at( cham )->theChamber.at( pos )->getRow();
				int c = theChambers.at( cham )->theChamber.at( pos )->getCol();
				dpos = rand() % 8;
				if ( dpos == 0 && theFloor[r-1][c-1]->getEmov() ) 
				{ 
					theFloor[r-1][c-1]->set( dra );
					break;
				}
				else if ( dpos == 1 && theFloor[r-1][c]->getEmov() ) 
				{
					theFloor[r-1][c]->set(dra);
					break;
				}
				else if ( dpos == 2 && theFloor[r-1][c+1]->getEmov() ) 
				{
					theFloor[r-1][c+1]->set( dra );
					break;
				}
				else if ( dpos == 3 && theFloor[r][c-1]->getEmov() ) 
				{
					theFloor[r][c-1]->set( dra );
					break;
				}
				else if ( dpos == 4 && theFloor[r][c+1]->getEmov() ) 
				{
					theFloor[r][c+1]->set( dra );
					break;
				}
				else if ( dpos == 5 && theFloor[r+1][c-1]->getEmov() ) 
				{
					theFloor[r+1][c-1]->set( dra );
					break;
				}
				else if ( dpos == 6 && theFloor[r+1][c]->getEmov() ) 
				{
					theFloor[r+1][c]->set( dra );
					break;
				}
				else if ( dpos == 7 && theFloor[r+1][c+1]->getEmov() ) 
				{
					theFloor[r+1][c+1]->set( dra );
					break;
				}
				 
			}
			theChambers.at( cham )->remove( pos ); 
		}
	}
}

void Floor::moveEnemies()
{
  int len = theEnemies.size();
  std::cout << "Enemy size " << len << std::endl;
  srand( time(NULL) );
  std::string randPos[8] = {"no", "ea", "we", "so", "nw", "ne", "se", "sw"};
  for ( int i = 0; i < len; ++i )
  {
    int rng = rand() % 8;
    move( theEnemies[i], randPos[rng]);
  }
}

void Floor::move( Character* cp1, std::string direction )
{
  int startRow = cp1->getRow();
  int startCol = cp1->getCol();
  if ( direction == "no" )
  {
    if (cp1->getType() == "player"? theFloor[startRow-1][startCol]->getPmov() : theFloor[startRow-1][startCol]->getEmov()) 
    { 
      theFloor[startRow-1][startCol]->set( theFloor[startRow][startCol]->getCp() );
      cp1->mutRow(startRow-1);
      theFloor[startRow][startCol]->unSet();
      theFloor[startRow-1][startCol]->notifyNbors();
    }
  }
  else if ( direction == "nw" )
  {
    if (cp1->getType() == "player"?  theFloor[startRow-1][startCol-1]->getPmov() :  theFloor[startRow-1][startCol-1]->getEmov()) 
    {  
       theFloor[startRow-1][startCol-1]->set( theFloor[startRow][startCol]->getCp() );
       cp1->mutRow(startRow-1);
       cp1->mutCol(startCol-1);
       theFloor[startRow][startCol]->unSet();
       theFloor[startRow-1][startCol-1]->notifyNbors();
    }
  }
  else if ( direction == "ne" )
  {
    if (cp1->getType() == "player"? theFloor[startRow-1][startCol+1]->getPmov() :  theFloor[startRow-1][startCol+1]->getEmov()) 
    {  
      theFloor[startRow-1][startCol+1]->set( theFloor[startRow][startCol]->getCp() );
      cp1->mutRow(startRow-1);
      cp1->mutCol(startCol+1);
      theFloor[startRow][startCol]->unSet();
      theFloor[startRow-1][startCol+1]->notifyNbors();
    }
  }
  else if (direction == "so")
  {
    if (cp1->getType() == "player"?  theFloor[startRow+1][startCol]->getPmov() :  theFloor[startRow+1][startCol]->getEmov()) 
    {  
      theFloor[startRow+1][startCol]->set( theFloor[startRow][startCol]->getCp() );
      cp1->mutRow(startRow+1);
      theFloor[startRow][startCol]->unSet();
      theFloor[startRow+1][startCol]->notifyNbors();
    }
  }
  else if (direction == "se")
  {
    if (cp1->getType() == "player"?  theFloor[startRow+1][startCol+1]->getPmov() :  theFloor[startRow+1][startCol+1]->getEmov()) 
    {  
      theFloor[startRow+1][startCol+1]->set( theFloor[startRow][startCol]->getCp() );
      cp1->mutRow(startRow+1);
      cp1->mutCol(startCol+1);
      theFloor[startRow][startCol]->unSet();
      theFloor[startRow+1][startCol+1]->notifyNbors();
    }
  }
  else if (direction == "sw")
  {
    if (cp1->getType() == "player"?  theFloor[startRow+1][startCol-1]->getPmov() :  theFloor[startRow+1][startCol-1]->getEmov())
    {  
      theFloor[startRow+1][startCol-1]->set( theFloor[startRow][startCol]->getCp() );
      cp1->mutRow(startRow+1);
      cp1->mutCol(startCol-1);
      theFloor[startRow][startCol]->unSet();
      theFloor[startRow+1][startCol-1]->notifyNbors();
    }
  }
  else if (direction == "ea")
  {
    if (cp1->getType() == "player" ?  theFloor[startRow][startCol+1]->getPmov() :  theFloor[startRow][startCol+1]->getEmov()) 
    {  
      theFloor[startRow][startCol+1]->set( theFloor[startRow][startCol]->getCp() );
      cp1->mutCol(startCol+1);
      theFloor[startRow][startCol]->unSet();
      theFloor[startRow][startCol+1]->notifyNbors();
    }
  }
  else if (direction == "we")
  {
    if (cp1->getType() == "player" ?  theFloor[startRow][startCol-1]->getPmov() :  theFloor[startRow][startCol-1]->getEmov()) 
    {  
      theFloor[startRow][startCol-1]->set( theFloor[startRow][startCol]->getCp() );
      cp1->mutCol(startCol-1);
      theFloor[startRow][startCol]->unSet();
      theFloor[startRow][startCol-1]->notifyNbors();
    }
  }
  if( isAtStairs() ) std::cout << isWon() << std::endl;
  if ( isAtPotion() ) 
  {
    consumePotion();
    theFloor[cp1->getRow()][cp1->getCol()]->removePotion();
  }
  if ( isAtTreasure() )
  {
    consumeTreasure( theFloor[ mainChar->getRow() ][ mainChar->getCol() ]->getTreasure() ); 
    theFloor[cp1->getRow()][cp1->getCol()]->removeTreasure(); 
  }
}

void Floor::attack( std::string direction )
{
//  int currHP = mainChar->getHp();

  if ( direction == "no" )
  {
    if ( theFloor[mainChar->getRow()-1][mainChar->getCol()]->getCp() && theFloor[mainChar->getRow()-1][mainChar->getCol()]->getCp()->getType() == "enemy" )
    {
      static_cast<Enemy*>(theFloor[mainChar->getRow()-1][mainChar->getCol()]->getCp())->attackedBy( *static_cast<Player*>(mainChar) );
//      double a = mainChar->getAtk();
//      double b = theFloor[mainChar->getRow()-1][mainChar->getCol()]->getCp()->getDef();
//      int dmg = ceil( ( 100 / ( 100 + b )  ) * a );
//      if ( currHP ==  mainChar-)	
      if( theFloor[mainChar->getRow()-1][mainChar->getCol()]->getCp()->getDead() ) slainEnemy(  static_cast<Enemy*>(theFloor[mainChar->getRow()-1][mainChar->getCol()]->getCp() ));
    }
  }
  else if ( direction == "so" )
  {
    if ( theFloor[mainChar->getRow()+1][mainChar->getCol()]->getCp() && theFloor[mainChar->getRow()+1][mainChar->getCol()]->getCp()->getType() == "enemy" )
    {
      static_cast<Enemy*>(theFloor[mainChar->getRow()+1][mainChar->getCol()]->getCp())->attackedBy( *static_cast<Player*>(mainChar) );
      if( theFloor[mainChar->getRow()+1][mainChar->getCol()]->getCp()->getDead() ) slainEnemy(  static_cast<Enemy*>(theFloor[mainChar->getRow()+1][mainChar->getCol()]->getCp() ));
    }
  }
  else if ( direction == "ea" )
  {
    if ( theFloor[mainChar->getRow()][mainChar->getCol()+1]->getCp() && theFloor[mainChar->getRow()][mainChar->getCol()+1]->getCp()->getType() == "enemy" )
    {
      static_cast<Enemy*>(theFloor[mainChar->getRow()][mainChar->getCol()+1]->getCp())->attackedBy( *static_cast<Player*>(mainChar) );
      if( theFloor[mainChar->getRow()][mainChar->getCol()+1]->getCp()->getDead() ) slainEnemy( static_cast<Enemy*>( theFloor[mainChar->getRow()][mainChar->getCol()+1]->getCp()) );
    }
  }
  else if ( direction == "we" )
  {
    if ( theFloor[mainChar->getRow()][mainChar->getCol()-1]->getCp() && theFloor[mainChar->getRow()][mainChar->getCol()-1]->getCp()->getType() == "enemy" )
    {
      static_cast<Enemy*>(theFloor[mainChar->getRow()][mainChar->getCol()-1]->getCp())->attackedBy( *static_cast<Player*>(mainChar) );
      if( theFloor[mainChar->getRow()][mainChar->getCol()-1]->getCp()->getDead() ) slainEnemy(  static_cast<Enemy*>(theFloor[mainChar->getRow()][mainChar->getCol()-1]->getCp() ));
    }
  }
  else if ( direction == "nw" )
  {
    if ( theFloor[mainChar->getRow()-1][mainChar->getCol()-1]->getCp() && theFloor[mainChar->getRow()-1][mainChar->getCol()-1]->getCp()->getType() == "enemy" )
    {
      static_cast<Enemy*>(theFloor[mainChar->getRow()-1][mainChar->getCol()-1]->getCp())->attackedBy( *static_cast<Player*>(mainChar) );
      if( theFloor[mainChar->getRow()-1][mainChar->getCol()-1]->getCp()->getDead() ) slainEnemy( static_cast<Enemy*>( theFloor[mainChar->getRow()-1][mainChar->getCol()-1]->getCp() ));
    }
  }
  else if ( direction == "ne" )
  {
    if ( theFloor[mainChar->getRow()-1][mainChar->getCol()+1]->getCp() && theFloor[mainChar->getRow()-1][mainChar->getCol()+1]->getCp()->getType() == "enemy" )
    {
      static_cast<Enemy*>(theFloor[mainChar->getRow()-1][mainChar->getCol()+1]->getCp())->attackedBy( *static_cast<Player*>(mainChar) );
      if( theFloor[mainChar->getRow()-1][mainChar->getCol()+1]->getCp()->getDead() ) slainEnemy(  static_cast<Enemy*>(theFloor[mainChar->getRow()-1][mainChar->getCol()+1]->getCp() ));
    }
  }
  else if ( direction == "se" )
  {
    if ( theFloor[mainChar->getRow()+1][mainChar->getCol()+1]->getCp() && theFloor[mainChar->getRow()+1][mainChar->getCol()+1]->getCp()->getType() == "enemy" )
    {
      static_cast<Enemy*>(theFloor[mainChar->getRow()+1][mainChar->getCol()+1]->getCp())->attackedBy( *static_cast<Player*>(mainChar) );
      if( theFloor[mainChar->getRow()+1][mainChar->getCol()+1]->getCp()->getDead() ) slainEnemy( static_cast<Enemy*>( theFloor[mainChar->getRow()+1][mainChar->getCol()+1]->getCp() ));
    }
  }
  else if ( direction == "sw" )
  {
    if ( theFloor[mainChar->getRow()+1][mainChar->getCol()-1]->getCp() && theFloor[mainChar->getRow()+1][mainChar->getCol()-1]->getCp()->getType() == "enemy" )
    {
      static_cast<Enemy*>(theFloor[mainChar->getRow()+1][mainChar->getCol()-1]->getCp())->attackedBy( *static_cast<Player*>(mainChar) );
      if( theFloor[mainChar->getRow()+1][mainChar->getCol()-1]->getCp()->getDead() ) slainEnemy(  static_cast<Enemy*>(theFloor[mainChar->getRow()+1][mainChar->getCol()-1]->getCp() ));
    }
  }
}


bool Floor::isAtStairs() { return theFloor[mainChar->getRow()][mainChar->getCol()]->getStair(); }
bool Floor::isAtPotion() { return theFloor[mainChar->getRow()][mainChar->getCol()]->getPot(); }
bool Floor::isAtTreasure() { return theFloor[mainChar->getRow()][mainChar->getCol()]->getTre(); }

void Floor::consumeTreasure( std::string s )
{
  Player * temp2;
  if ( s == "small" ) temp2 = new Small{mainChar};
  else if ( s == "normal" ) temp2 = new Normal{mainChar};
  else if ( s == "dragon" ) temp2 = new DragonHoard{mainChar};
  else if ( s == "merchant" ) temp2 = new MerchantHoard{mainChar};
  mainChar->setGold( temp2->getGold() );
  delete temp2;
}


void Floor::gameOver() {};

void Floor::consumePotion()
{ 
  srand( time(NULL) );
  int rng = rand() % 6; 
  //make temp copy of main char on heap
  Player * temp2;
  if ( rng == 0 )  temp2= new BoostAtk{mainChar};
  else if ( rng == 1 ) temp2 = new BoostDef{mainChar};
  else if ( rng == 2 ) temp2 = new WoundAtk{mainChar};
  else if ( rng == 3 ) temp2 = new WoundDef{mainChar};
  else if ( rng == 4 ) temp2  = new RestoreHealth{mainChar};
  else temp2 = new PoisonHealth{mainChar};
  if ( temp2->getHP() <= 0 )
  {
    gameOver();
    return;
  }

  mainChar->setHP( temp2->getHP() );
  mainChar->setDef( temp2->getDef() );
  mainChar->setAtk( temp2->getAtk() );
  delete temp2;
}


std::string Floor::isWon()
{
	if ( level == 5 ){ 
            // throw std::logic_error;
             return "WIN!";
}
	else 
	{ 
		++level;
		init();
		return "New Floor!";
	}
}

void Floor::slainEnemy( Enemy* e )
{
  if ( mainChar->getRace() == "Goblin" )
  {
    mainChar->mutGold(5);
    theFloor[e->getRow()][e->getCol()]->unSet();
  }
  if ( e->getRace() == "Merchant" )
  {
    theFloor[e->getRow()][e->getCol()]->unSet();
    theFloor[e->getRow()][e->getCol()]->setTreasure( "merchant" );  
  }
  else if ( e->getRace() == "Dragon" )
  {
    theFloor[e->getRow()][e->getCol()]->unSet();
  }
  else 
  {
    srand( time(NULL));
    mainChar->mutGold( rand() % 1 + 1 );
    theFloor[e->getRow()][e->getCol()]->unSet();
  }
}

std::ostream &operator<<(std::ostream &out, const Floor &f) 
{
  for(int row = 0; row < 25; row++)
  {
    for(int col = 0; col < 80; col++) 
    {
      if ( f.theFloor[row][col]->getCp() ) { out << f.theFloor[row][col]->getCp()->getSymbol(); }
      else out << f.theFloor[row][col]->getSymbol();
    }
  }
  out << "Race: "<< f.mainChar->getRace() << " Gold: " << f.mainChar->getGold();
  out << "						Floor " << f.level << std::endl;
  out << "HP: " << f.mainChar->getHP() << std::endl;
  out << "Atk: " << f.mainChar->getAtk() << std::endl;
  out << "Def: " << f.mainChar->getDef() << std::endl;
  out << "Action:" << std::endl; 
  return out;
}

