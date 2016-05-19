//Ryan Hayes
//Spring 2016
//Computer player class

#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "Lexicon.h"
#include "BoggleBoard.h"
#include <set>
#include <string>

class ComputerPlayer
{
public:
	ComputerPlayer(const Lexicon& lexicon);
	virtual ~ComputerPlayer(void);

	//driver function uses by computer player to play boggle
	std::set<std::string> playBoggle(int minLetters, BoggleBoard& board,const std::set<std::string>& humanWords);	

private:
	//helper function to help computer player play boggle
	void playBoggle(std::string& word, int row, int column, int minLetters, BoggleBoard& board, 
		std::set<std::string>& computerWords, const std::set<std::string>& humanWords);

private:
	Lexicon lexicon_;
};

#endif
