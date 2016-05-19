#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(const Lexicon& lexicon)
{
	lexicon_ = lexicon;
}

ComputerPlayer::~ComputerPlayer(void)
{
}

//driver function for play boggle
std::set<std::string> ComputerPlayer::playBoggle(int minLetters, BoggleBoard& board,const std::set<std::string>& humanWords)
{	
	std::set<std::string> computerWords;
	for(int i = 0;i < board.getWidth();++i)							//go through every square on the board
	{
		for(int j = 0;j < board.getWidth();++j)
		{	
			std::string word = "";							//create blank word
			char letter = board.getLetter(i,j);					//save the first letter
			word += letter;								//and add that to the word
			board.setLetter('?', i, j);						//set that spot on the board to used
			playBoggle(word, i, j, minLetters, board, computerWords, humanWords);	//and recurse
			board.setLetter(letter, i, j);						//then set back
		}
	}
	return computerWords;
}

//helper function for play boggle
void ComputerPlayer::playBoggle(std::string& word, int row, int column, int minLetters, 
	BoggleBoard& board, std::set<std::string>& computerWords, const std::set<std::string>& humanWords)
{
	for(int i = -1;i <= 1;++i)			//go through all adjacent squares
	{
		for(int j = -1;j <= 1;++j)
		{
			int nextRow = i + row;
                        int nextColumn = j + column;
                        if((i != 0 || j != 0) && nextRow > -1 && nextColumn > -1 && nextRow < board.getWidth()
                               && nextColumn < board.getWidth() && board.getLetter(nextRow, nextColumn) != '?')//make sure the spots are valid
                        {
				char newLetter = board.getLetter(nextRow, nextColumn);			   //get the letter from that spot
				word += newLetter;							   //and add it to the word
        			Lexicon::Status status = lexicon_.wordStatus(word);			   //then get the status of that word
        			if(status == Lexicon::WORD && word.size() >= minLetters && humanWords.count(word) < 1)	//if the word fits requirements
        			{
               				 computerWords.insert(word);							//push on to word map
        			}
				if(status == Lexicon::WORD || status == Lexicon::WORD_PREFIX)				//if we have word or word prefix
				{
        	                        board.setLetter('?', nextRow, nextColumn); 				//set equal to a character that wont come up
	                                playBoggle(word, nextRow, nextColumn, minLetters, board, computerWords, humanWords);//then recurse
                                        board.setLetter(newLetter, nextRow, nextColumn);			//then set back
				}
				word.resize(word.size()-1);							//then reduce word size
                        }
		}
	}
}

