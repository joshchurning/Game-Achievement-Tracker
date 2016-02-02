/* ------------------------------------------------------------------------------
This software is in the public domain, furnished "as is", without technical
support, and with no warranty, express or implied, as to its usefulness for
any purpose.
  
File: Achievement.h
  
Author: Joshua Churning

Date: January 28, 2016
------------------------------------------------------------------------------ */
#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <string>

using namespace std;

class Achievement {
  public:
	int id;
	string name;
	int points;

	Achievement(int, string, int);
};

/*-----------------------------------------------------------------
CONSTRUCTOR
-----------------------------------------------------------------*/
Achievement::Achievement (int x, string y, int z) {
	id = x;
	name = y;
	points = z;
}

#endif
