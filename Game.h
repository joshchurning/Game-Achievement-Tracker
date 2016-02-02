/* ------------------------------------------------------------------------------
This software is in the public domain, furnished "as is", without technical
support, and with no warranty, express or implied, as to its usefulness for
any purpose.
  
File: Game.h
  
Author: Joshua Churning

Date: January 28, 2016
------------------------------------------------------------------------------ */
#ifndef GAME_H
#define GAME_H

#include "Achievement.h"
#include <string>
#include <vector>

using namespace std;

class Game {
  public:
	int id;
	string name;
	vector<Achievement> Achievements;	// Total achievements for the game
	
  	Game (int, string);
};

/*-----------------------------------------------------------------
CONSTRUCTOR
-----------------------------------------------------------------*/
Game::Game (int _id, string _name) {
	id = _id;
	name = _name;
}

#endif
