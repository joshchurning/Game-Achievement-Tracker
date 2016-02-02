/* ------------------------------------------------------------------------------
This software is in the public domain, furnished "as is", without technical
support, and with no warranty, express or implied, as to its usefulness for
any purpose.
  
File: GamePlayed.h
  
Author: Joshua Churning

Date: January 28, 2016
------------------------------------------------------------------------------ */
#ifndef GAMEPLAYED_H
#define GAMEPLAYED_H

#include "Achievement.h"
#include <string>
#include <vector>

using namespace std;

class GamePlayed {
  public:
	int id;
	string name;
	string IGN;	// In game name
	vector<int> achievementsCompleted;
	int gamerscore;

	GamePlayed (int, string, string);
};

/*-----------------------------------------------------------------
CONSTRUCTOR
-----------------------------------------------------------------*/
GamePlayed::GamePlayed (int x, string y, string z) {
	id = x;
	IGN = y;
	name = z;
	gamerscore= 0;
}

#endif
