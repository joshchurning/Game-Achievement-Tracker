/* ------------------------------------------------------------------------------
This software is in the public domain, furnished "as is", without technical
support, and with no warranty, express or implied, as to its usefulness for
any purpose.
  
File: GameAchievementTracker.h
  
Author: Joshua Churning

Date: January 28, 2016
------------------------------------------------------------------------------ */
#ifndef GameAchievementTracker_H
#define GameAchievementTracker_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "GamePlayed.h"
#include "Game.h"
#include "Player.h"
#include "Achievement.h"

using namespace std;

class GameAchievementTracker {
  private:
	vector<Player> allPlayers;
	vector<Game> allGames;

  public:
	int FindPlayerKey (int playerID);

	int FindGameKey (int gameID);

	int FindGamePlayedKey (Player player, int gameID);

	int FindAchievementKey (int gameID, int achievementID);

	int FindCompletedAchievementKey (GamePlayed currentGame, int achievementID);

	void AddPlayer (int playerID, string playerName);

	void AddGame (int gameID, string gameName);

	void AddAchievement (int gameID, int achievementID, string achievementName, int achievementPoints);

	void Plays (int playerID, int gameID, string playerIGN);

	void AddFriends (int playerID1, int playerID2);

	void Achieve (int playerID, int gameID, int achievementID);

	void FriendsWhoPlay (int playerID, int gameID);

	void ComparePlayers (int playerID1, int playerID2, int gameID);

	void SummarizePlayer(int playerID);

	void SummarizeGame (int gameID);

	void SummarizeAchievement (int gameID, int achievementID);

	void AchievementRanking ();

	void ReadInput ();
};

/*---------------------------------------------------------------
Searches for Player based on Player ID and returns the index 
in the allPlayers vector. If there is an error it returns -1
---------------------------------------------------------------*/
int GameAchievementTracker::FindPlayerKey (int playerID) {
	int key = -1;
	for (int i=0; i<allPlayers.size(); i++) {
		if (playerID == allPlayers[i].id) {
			key = i;
		}
	}
	if (key == -1){
		cerr << "Player Not Found" << endl;
	}
	return key;	
}

/*---------------------------------------------------------------
Searches for Game based on Game ID and returns the index 
in the allGames vector. If there is an error it returns -1
---------------------------------------------------------------*/
int GameAchievementTracker::FindGameKey (int gameID) {
	int key = -1;
	for (int i=0; i<allGames.size(); i++) {
		if (gameID == allGames[i].id) {
			key = i;
		}
	}
	if (key == -1){
		cerr << "Game Not Found" << endl;
	}
	return key;	
}

/*---------------------------------------------------------------
Searches for Game the player has played based on Player and 
Game ID and returns index in the gamesPlayed vector inside that
player's class. If there is an error it returns -1
---------------------------------------------------------------*/
int GameAchievementTracker::FindGamePlayedKey (Player player, int gameID) {
	int key = -1;
	for (int i=0; i<player.gamesPlayed.size(); i++) {
		if (gameID == player.gamesPlayed[i].id) {
			key = i;
		}
	}
	return key;	
}

/*---------------------------------------------------------------------
Searches for Achievement based on Game ID and Achievement ID and
returns the index in the Achievements vector in the that Game 
object inside the allGames vector. If there is an error it returns -1
---------------------------------------------------------------------*/
int GameAchievementTracker::FindAchievementKey (int gameID, int achievementID) {
	int gamekey = FindGameKey (gameID);
	Game currentGame = allGames[gamekey];
	
	int key = -1;
	for (int i=0; i<currentGame.Achievements.size(); i++) {
		if (achievementID == currentGame.Achievements[i].id) {
			key = i;
		}
	}
	if (key == -1) {
		cerr << "Achievement Not Found" << endl;
	}

	return key;
}

/*---------------------------------------------------------------
Searches for Achievement based on GamePlayed and Achievement ID 
and returns the index in the AchievementsCompleted vector which
is a member in that Player. If there is an error it returns -1
---------------------------------------------------------------*/
int GameAchievementTracker::FindCompletedAchievementKey (GamePlayed currentGame, int achievementID) {
	int key = -1;
	for (int i=0; i<currentGame.achievementsCompleted.size(); i++) {
		if (achievementID == currentGame.achievementsCompleted[i]) {
			key = i;
		}
	}

	return key;
}

/*---------------------------------------------------------------
Add player object to database
---------------------------------------------------------------*/
void GameAchievementTracker::AddPlayer (int playerID, string playerName) {
		Player newPlayer(playerID, playerName);
		allPlayers.push_back(newPlayer);
}

/*---------------------------------------------------------------
Add game object to database
---------------------------------------------------------------*/
void GameAchievementTracker::AddGame (int gameID, string gameName) {
	// Check for duplicate gameID in database
	for (int i = 0; i<allGames.size(); i++) {
		if (allGames[i].id == gameID) {
			cout << "ERROR: DUPLICATE Game id" << endl;
		}
	}

	Game newGame(gameID, gameName);
	allGames.push_back(newGame);
}

/*---------------------------------------------------------------
Add achievement object to a specific game
---------------------------------------------------------------*/
void GameAchievementTracker::AddAchievement (int gameID, int achievementID, string achievementName, int achievementPoints) {
	int key = -1;
	for (int i = 0; i<allGames.size(); i++) {
		if (allGames[i].id == gameID) {
			key = i;
		}
	}

	// Error check for game not found
	if (key != -1) {
		Achievement newAchievement (achievementID, achievementName, achievementPoints);
		allGames[key].Achievements.push_back(newAchievement);
	}
}

/*---------------------------------------------------------------
Add game played objcet to a specific player
---------------------------------------------------------------*/
void GameAchievementTracker::Plays (int playerID, int gameID, string playerIGN) {
	int playerKey = -1;
	for (int i = 0; i<allPlayers.size(); i++) {
		if (allPlayers[i].id == playerID) {
			playerKey = i;
		}
	}

	int gameKey = -1;
	for (int i = 0; i<allGames.size(); i++) {
		if (allGames[i].id == gameID) {
			gameKey = i;
		}
	}

	// Error check to make sure player and game exist
	if (gameKey != -1 && playerKey != -1) {
		GamePlayed newGamePlayed (gameID, playerIGN, allGames[gameKey].name);
		allPlayers[playerKey].gamesPlayed.push_back(newGamePlayed);	
	}
}

/*---------------------------------------------------------------
Add Player 2's ID to Player 1's friends vector and vice versa
---------------------------------------------------------------*/
void GameAchievementTracker::AddFriends (int playerID1, int playerID2) {
	int playerKey1, playerKey2 = -1;
	if (playerID1 == playerID2) {
		cout << "ERROR: SAME PLAYER id FOR BOTH FRIENDS" << endl;
	}
	else {
		for (int i = 0; i<allPlayers.size(); i++) {
			if (allPlayers[i].id == playerID1) {
				playerKey1 = i;
			}
		}

		for (int i = 0; i<allPlayers.size(); i++) {
			if (allPlayers[i].id == playerID2) {
				playerKey2 = i;
			}
		}

		// Error check to make sure both players exist
		if (playerKey1 != -1 && playerKey2 != -1) {
			allPlayers[playerKey1].friends.push_back(playerID2);
			allPlayers[playerKey2].friends.push_back(playerID1);
		}
	}
}

/*---------------------------------------------------------------
Add achievement ID to specific players achievementsCompleted
vector and then increase their gamerscore
---------------------------------------------------------------*/
void GameAchievementTracker::Achieve (int playerID, int gameID, int achievementID) {
	int playerKey = FindPlayerKey (playerID);
	int gameKey = FindGameKey (gameID);
	int gamePlayedKey = FindGamePlayedKey (allPlayers[playerKey], gameID);
	
	if (gamePlayedKey == -1) {
		cout << "Player: " << playerID << " does not play game " << gameID << endl;
	}
	else {
		Player currentPlayer = allPlayers[playerKey];
		GamePlayed currentGamePlayed = currentPlayer.gamesPlayed[gamePlayedKey];
		Game currentGame = allGames[gameKey];

		int achievementKey = FindAchievementKey (gameID, achievementID);
		Achievement currentAchievement = currentGame.Achievements[achievementKey];
		
		int achievementPoints = currentAchievement.points;
		currentPlayer.gamerscore += achievementPoints;
		currentGamePlayed.gamerscore += achievementPoints;
		currentGamePlayed.achievementsCompleted.push_back(achievementID);

		allPlayers[playerKey] = currentPlayer;
		allPlayers[playerKey].gamesPlayed[gamePlayedKey] = currentGamePlayed;
	}
}

/*---------------------------------------------------------------
Display all of that player's friends who play a certain game
---------------------------------------------------------------*/
void GameAchievementTracker::FriendsWhoPlay (int playerID, int gameID) {
	int key = FindPlayerKey(playerID);
	Player currentPlayer = allPlayers[key];
	
	int width = 20;
	cout << endl << "Player: " << currentPlayer.name;
	cout << endl << endl;

	cout << left << setw(10) << "" << setw(width) << "Name" << endl;
	cout << "         -------------------------------------------------------------------" << endl;

	cout << left << setw(10) << "Friends:";

	for (int i=0; i<currentPlayer.friends.size(); i++) {
		int friendKey = FindPlayerKey(currentPlayer.friends[i]);
		Player currentFriend = allPlayers[friendKey];

		int gameKey = FindGamePlayedKey(currentFriend, gameID);
		if (gameKey != -1) {
			cout << setw(width) << currentFriend.name << endl;
		}
	}
	cout << endl << endl;
}

/*-----------------------------------------------------------------
Display information comparing two players stats on a similar game
-----------------------------------------------------------------*/
void GameAchievementTracker::ComparePlayers (int playerID1, int playerID2, int gameID) {
	int firstPlayerKey = FindPlayerKey(playerID1);
	int secondPlayerKey = FindPlayerKey(playerID2);

	Player firstPlayer = allPlayers[firstPlayerKey];
	Player secondPlayer = allPlayers[secondPlayerKey];

	int firstGameKey = FindGamePlayedKey(firstPlayer, gameID);
	int secondGameKey = FindGamePlayedKey(secondPlayer, gameID);

	GamePlayed firstGame = firstPlayer.gamesPlayed[firstGameKey];
	GamePlayed secondGame = secondPlayer.gamesPlayed[secondGameKey];

	int width = 20;
	cout << endl << "Game: " << firstGame.name << endl << endl;
	cout << left << setw(10) << "" << setw(width) << "Name";
	cout << left << setw(width) << "Achievements";
	cout << left << setw(width) << "Gamerscore" << endl;
	cout << "         -------------------------------------------------------------------" << endl;
	cout << left << setw(10) << "Friends:";

	cout << left << setw(width) << firstPlayer.name;
	string completedAchievementsString = to_string(firstGame.achievementsCompleted.size());
	string totalAchievementsString = to_string(allGames[FindGameKey(firstGame.id)].Achievements.size());
	string achievementString = completedAchievementsString + "/" + totalAchievementsString;	
	cout << setw(width) << achievementString;
	cout << setw(width) << firstGame.gamerscore << endl;

	cout << setw(10) << "" << left << setw(width) << secondPlayer.name;
	completedAchievementsString = to_string(secondGame.achievementsCompleted.size());
	totalAchievementsString = to_string(allGames[FindGameKey(secondGame.id)].Achievements.size());
	achievementString = completedAchievementsString + "/" + totalAchievementsString;
	cout << setw(width) << achievementString;
	cout << setw(width) << secondGame.gamerscore << endl;

	cout << endl << endl;
}

/*---------------------------------------------------------------
Display all of a player's stats and a list of their friends
---------------------------------------------------------------*/
void GameAchievementTracker::SummarizePlayer(int playerID) {
	int key = FindPlayerKey(playerID);
	Player currentPlayer = allPlayers[key];
	int width = 20;
	
	cout << endl << "Player: " << currentPlayer.name;
	cout << "     Total gamerscore: " << currentPlayer.gamerscore << endl;

	cout << left << setw(10) << "" << setw(width) << "Name";
	cout << left << setw(width) << "Achievements";
	cout << left << setw(width) << "Gamerscore";
	cout << left << setw(width) << "IGN" << endl;
	cout << "         -------------------------------------------------------------------" << endl;

	cout << left << setw(10) << "Games:";

	for (int i = 0; i<currentPlayer.gamesPlayed.size(); i++) {
		if (i > 0) {
			cout << setw(10) << "";
		}

		GamePlayed currentGame = currentPlayer.gamesPlayed[i];

		cout << setw(1) << currentGame.id << setw(1) << ". " << setw(width) << currentGame.name;

		string completedAchievementsString = to_string(currentGame.achievementsCompleted.size());
		string totalAchievementsString = to_string(allGames[FindGameKey(currentGame.id)].Achievements.size());
		string achievementString = completedAchievementsString + "/" + totalAchievementsString;

		cout << setw(width) << achievementString;
		cout << setw(width) << currentGame.gamerscore;
		cout << setw(width) << currentGame.IGN << endl;
	}
	cout << endl << endl;

	cout << left << setw(10) << "" << setw(width) << "Name";
	cout << left << setw(width) << "Gamerscore" << endl;
	cout << "         -------------------------------------------------------------------" << endl;

	cout << left << setw(10) << "Friends:";

	for (int i = 0; i<currentPlayer.friends.size(); i++) {
		if (i > 0) {
			cout << setw(10) << "";
		}
		for (int x = 0; x<allPlayers.size(); x++) {
			if (allPlayers[x].id == allPlayers[key].friends[i]) {
				cout << setw(width) << allPlayers[x].name;
				cout << setw(width) << allPlayers[x].gamerscore << endl;
			}
		}
	}
	cout << endl << endl;
}

/*---------------------------------------------------------------
Display all of the players' stats on a specific game
---------------------------------------------------------------*/
void GameAchievementTracker::SummarizeGame (int gameID) {
	int gameKey = FindGameKey(gameID);
	Game currentGame = allGames[gameKey];

	cout << endl << "Game: " << currentGame.name << endl;


	int width = 20;
	cout << left << setw(10) << "" << setw(width) << "Name";
	cout << left << setw(width) << "Achievements";
	cout << left << setw(width) << "Gamerscore";
	cout << left << setw(width) << "IGN" << endl;
	cout << "         -------------------------------------------------------------------" << endl;

	for (int i=0; i<allPlayers.size(); i++) {
		Player currentPlayer = allPlayers[i];

		int gamePlayedKey = FindGamePlayedKey(currentPlayer, gameID);
		
		if (gamePlayedKey != -1) {
		
			GamePlayed currentGamePlayed = currentPlayer.gamesPlayed[gamePlayedKey];

			cout << left << setw(10) << "" << setw(width) << currentPlayer.name;
			
			string completedAchievementsString = to_string(currentGamePlayed.achievementsCompleted.size());
			string totalAchievementsString = to_string(allGames[FindGameKey(currentGamePlayed.id)].Achievements.size());
			string achievementString = completedAchievementsString + "/" + totalAchievementsString;
			
			cout << setw(width) << achievementString;
			cout << setw(width) << currentGamePlayed.gamerscore;
			cout << setw(width) << currentGamePlayed.IGN << endl;
		}

	}

	cout << endl;
	
}

/*-----------------------------------------------------------------
Display all the players who have completed a specific achievement
-----------------------------------------------------------------*/
void GameAchievementTracker::SummarizeAchievement (int gameID, int achievementID) {
	int gameKey = FindGameKey(gameID);
	cout << endl << "Game: " << allGames[gameKey].name;
	cout << endl << "Achievement: " << achievementID << endl;

	int width = 20;
	cout << left << setw(10) << "" << setw(width) << "Name" << endl;
	cout << "         -------------------------------------------------------------------" << endl;
	cout << left << setw(10) << "Players:";
	
	float found = 0;
	for (int i=0; i<allPlayers.size(); i++){
		Player currentPlayer = allPlayers[i];
		
	
		int gamePlayedKey = FindGamePlayedKey(currentPlayer, gameID);
		if (gamePlayedKey != -1){
			GamePlayed currentGame = currentPlayer.gamesPlayed[gamePlayedKey];
			
			int completedAchievementKey = FindCompletedAchievementKey(currentGame, achievementID);
			
			if (completedAchievementKey != -1) {
				if (i > 0) {
					cout << left << setw(10) << "";
				}
				cout << left << setw(width) << currentPlayer.name << endl;
				found++;
			}
		}
	}

	cout << endl;
	float percentage = (found / allPlayers.size()) * 100;
	cout << "Percentage of Player who have achieved: " << percentage << "%";
	cout << endl << endl;
}


/*---------------------------------------------------------------
Sort the allPlayers vector from highest to lowest gamerscore
and then display all the players and their score from highest
to lowest.
---------------------------------------------------------------*/
void GameAchievementTracker::AchievementRanking () {

	int width = 20;
	cout << "Achievement Ranking" << endl;
	cout << left << setw(10) << "" << setw(width) << "Name";
	cout << left << setw(width) << "Gamerscore" << endl;
	cout << "         -------------------------------------------------------------------" << endl;

	for (int i=0; i<allPlayers.size(); i++) {
		for (int j=0; j<allPlayers.size(); j++) {
			Player currentPlayer1 = allPlayers[i];
			Player currentPlayer2 = allPlayers[j];

			if (currentPlayer2.gamerscore < currentPlayer1.gamerscore) {
				swap(allPlayers[j], allPlayers[i]);
			}
		}
	}

	cout << left << setw(10) << "Players:";

	for (int i=0; i<allPlayers.size(); i++) {
		if (i>0){
			cout << left << setw(10) << "" ;
		}

		cout << left << setw(width) << allPlayers[i].name;
		cout << left << setw(width) << allPlayers[i].gamerscore << endl;
	}

	cout << endl;

}

/*---------------------------------------------------------------
Take an input from standard input and then perform the 
functions that are implementated for this database
---------------------------------------------------------------*/
void GameAchievementTracker::ReadInput () {
	while (cin) {

		string line;
		getline(cin, line);
		
		stringstream input;
		input << line;

		string functionName;
		input >> functionName;

		if (functionName == "AddPlayer") {
			int playerID;
		

			input >> playerID;
			string playerName;
			char delimiter('"');
			getline(input, playerName, delimiter);
			getline(input, playerName, delimiter);
			
			AddPlayer(playerID, playerName);
		}
		else if (functionName == "AddGame") {
			int gameID;
			string gameName;

			input >> gameID;
			char delimiter('"');
			getline(input, gameName, delimiter);
			getline(input, gameName, delimiter);

			AddGame(gameID, gameName);
		}
		else if (functionName == "AddAchievement") {
			int gameID;
			int achievementID;
			int achievementPoints;

			input >> gameID;
			input >> achievementID;
	

			string achievementName;
			char delimiter('"');
			getline(input, achievementName, delimiter);
			getline(input, achievementName, delimiter);

			input >> achievementPoints;
			
			AddAchievement(gameID, achievementID, achievementName, achievementPoints);
		}
		else if (functionName == "Plays") {
			int playerID;
			int gameID;
			char delimiter('"');
			string playerIGN;
			input >> playerID;
			input >> gameID;
			getline(input, playerIGN, delimiter);
			getline(input, playerIGN, delimiter);
			Plays(playerID, gameID, playerIGN);
		}
		else if (functionName == "AddFriends") {
			int playerID1;
			int playerID2;
			input >> playerID1;
			input >> playerID2;
			AddFriends(playerID1,playerID2);
		}
		else if (functionName == "Achieve") {
			int playerID;
			int gameID;
			int achievementID;
			input >> playerID;
			input >> gameID;
			input >> achievementID;
			Achieve(playerID, gameID, achievementID);
		}
		else if (functionName == "FriendsWhoPlay") {
			int playerID;
			int gameID;
			input >> playerID;
			input >> gameID;
			FriendsWhoPlay(playerID, gameID);
		} 
		else if (functionName == "ComparePlayers") {
			int playerID1;
			int playerID2;
			int gameID;
			input >> playerID1;
			input >> playerID2;
			input >> gameID;
			ComparePlayers(playerID1, playerID2, gameID);
		}
		else if (functionName == "SummarizePlayer") {
			int playerID;
			input >> playerID;
			SummarizePlayer(playerID);
		}
		else if (functionName == "SummarizeGame") {
			int gameID;
			input >> gameID;
			SummarizeGame(gameID);
		}
		else if (functionName == "SummarizeAchievement") {
			int gameID;
			int achievementID;
			input >> gameID;
			input >> achievementID;
			SummarizeAchievement(gameID, achievementID);
		}
		else if (functionName == "AchievementRanking") {
			AchievementRanking();
		}
	}
}

#endif