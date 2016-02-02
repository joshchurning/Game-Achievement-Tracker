/* ------------------------------------------------------------------------------
This software is in the public domain, furnished "as is", without technical
support, and with no warranty, express or implied, as to its usefulness for
any purpose.
  
File: Main.cpp
  
Author: Joshua Churning

Date: January 28, 2016
------------------------------------------------------------------------------ */
#include <iostream>
#include <cstdlib>
#include "GameAchievementTracker.h"

using namespace std;

int main () {
	system("clear");
	GameAchievementTracker tracker;
	tracker.ReadInput();
}
