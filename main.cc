#include "character.h"
#include "player.h"
#include "enemy.h"
#include "shade.h"
#include "vampire.h"
#include "drow.h"
#include "troll.h"
#include "goblin.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "dragon.h"
#include "halfling.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "cell.h"
#include "floor.h"
#include <stdexcept>
bool move = true;
bool reborn = false;
int main() 
{
	while(true){
		reborn = false;
		std::string str;
		std::cout << "Choose your race" << std::endl;
		std::cout << "(S)hade, (D)row, (V)ampire, (T)roll, (G)oblin" << std::endl;
		std::string cmd;
		Floor *floor;
		int level = 1;
		int turn = 0;  
		//choose character
		while(std::cin >> cmd )
		{
			if (std::cin.eof()) return 0;

			else if (cmd == "s" || cmd == "S" || cmd == "D" || cmd == "d" || cmd == "V" || cmd == "v" || cmd == "T" || cmd == "t" || cmd == "G" || cmd == "g") 
			{ 
				floor = new Floor( 1, cmd );
				break;
			}
			else {
				std::cout << "Try again" << std::endl; 
			}
		}
		floor->init();
		std::cout << *floor;
		std::string s;

		//action loop:  
		while(std::cin >> s)
		{
			try{
				if(s == "no" || s == "so" || s == "ea" || s == "nw" || s == "ne" || s == "se" || s == "we" || s == "sw"){
					floor->move(floor->getMainChar(), s);
				} 
				if(s == "a"){
					std::string atkPos;
					std::cin >> atkPos;
					floor->attack(atkPos);
				}
				if(s == "f") { 
					move = !move;
					std::cout << "Enemy movement freeze!" << std::endl;
				}
				if(s == "q") {
					std::cout << "Admit defeat and quit the game" << std::endl;
					break;
				}
				if(s == "r") {
					reborn = !reborn;
					break;
				}
			}
			catch (std::bad_exception){//you are slained
				std::cout << "You are slained" << std::endl;
				break;
			}
                        catch (std::logic_error){
				std::cout << "You Win!" << std::endl;
                                break;
			}
			if(!reborn){
				if (move) floor->moveEnemies();
				std::cout << *floor;
			}
			else{
				break;
			}
		}
		if(!reborn) break;
	}
}



