# Game Achievement Tracker

# Requirements
Develop a command-line-interface application to keep track of video game players (ie. games the play, achievements accomplished, and friendships between players)

# Overview
This application is written in C++ and the input is taking in through standard input. You can type each command or pipe the commands in from a text file.

# Functions
<strong>AddPlayer</strong> PlayerID "Player Name" <br>
<strong>AddGame</strong> GameID "Game Name" <br>
<strong>AddAchievement</strong> GameID AchievementID "AchievementName" AchievementPoints <br>
<strong>Plays</strong> PlayerID GameID PlayerIGN <br>
<strong>AddFriends</strong> PlayedID1 PlayerID2<br>
<strong>Achieve</strong> PlayerID GameID AchievementID<br>
<strong>FriendsWhoPlay</strong> PlayerID GameID<br>
<strong>ComparePlayers</strong> PlayerID1 PlayerID2 GameID<br>
<strong>SummarizePlayer</strong> PlayerID<br>
<strong>SummarizeGame</strong> GameID<br>
<strong>SummarizeAchievement</strong> GameID AchievementID<br>
<strong>AchievementRanking</strong><br>

Note: Inputs are numbers unless they are surronded by double quotes. Those inputs must be surrounded by double quotes when being inputted.

# Compile / Run Instructions
<h3>Compile</h3>
simply type "make"
<h3>Run</h3>
An executable file called "main" will be created. To run it type "./main" . You can then either type the functions from the functions from the list above or pipe them in from a text file using "./main < testfile.txt"

# Thanks & Gig 'Em

