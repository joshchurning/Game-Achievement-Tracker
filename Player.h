/* ------------------------------------------------------------------------------
This software is in the public domain, furnished "as is", without technical
support, and with no warranty, express or implied, as to its usefulness for
any purpose.
  
File: Player.h
  
Author: Joshua Churning

Date: January 28, 2016
------------------------------------------------------------------------------ */
#ifndef PLAYER_H
#define PLAYER_H

#include "GamePlayed.h"
#include <string>
#include <vector>

using namespace std;

class Player {
  public:
	int id;
	string name;
	vector<int> friends;
	vector<GamePlayed> gamesPlayed;
	int gamerscore;
  	Player (int, string);
};

/*-----------------------------------------------------------------
CONSTRUCTOR
-----------------------------------------------------------------*/
Player::Player (int x, string y) {
	id = x;
	name = y;
	gamerscore = 0;
}

#endif
