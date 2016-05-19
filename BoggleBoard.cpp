#include "BoggleBoard.h"

//BoggleBoard methods
BoggleBoard::BoggleBoard(int width, BogglePieceGenerator& gen) : width_(width)
{
	normalize();	//create board
	construct(gen); //then add letters
}

BoggleBoard::~BoggleBoard(void)
{
	for(int i = 0;i < width_;++i)
        {
                delete [] board_[i];//delete all arrays
        }
        delete [] board_;//and final array
}

BoggleBoard::BoggleBoard(const BoggleBoard& rhs)
{
	normalize();
	copy(rhs);
}

BoggleBoard& BoggleBoard::operator =(const BoggleBoard& rhs)//equals operator for board
{
	copy(rhs);
	return *this;	
}

char BoggleBoard::getLetter(int row,int column)		    //returns a copy of the letter in that spot
{
	return board_[row][column];
}

void BoggleBoard::setLetter(char letter, int row, int column)//set a spot on the board equal to that letter
{
	board_[row][column] = letter; 
}
        
int BoggleBoard::getWidth()
{
	return width_;
}

bool BoggleBoard::isWordOnBoard(string word)
{
        bool retval = false;
	int i = 0;
	int j = 0;
	while((!retval) && i < width_)						//search for the first letter of the word
	{
		while((!retval) && j < width_)
		{
			if((!retval) && board_[i][j] == word[0])		//if we find the letter
			{
				retval = findAdjacencies(word, 1, i, j, board_);//recurse
			}
			++j;
		}
		++i;
		j = 0;
	}
	return retval;
}

bool BoggleBoard::findAdjacencies(string word, int wordCursor, int row, int column, char**& board)
{
       bool retval = false;
       int i = -1;
       int j = -1;
       while((!retval) && i <= 1)//while we havent found the word
       {

       		while((!retval) && j <= 1)
       		{
                	int nextRow = i + row;			//get the next row
                        int nextColumn = j + column;		//and next column
       			if((i != 0 || j != 0) && nextRow > -1 && nextColumn > -1 && nextRow < width_ 		//check new spots for letter
				&& nextColumn < width_ && board_[nextRow][nextColumn] == word[wordCursor])	//make sure spot is valid
                	{
                        	char actualLetter = board_[row][column];					//save character
                        	board_[row][column] = '?'; //set equal to a character that wont come up		//change that spot to a new char
                        	++wordCursor;									//move to next spot in word
                        	retval = findAdjacencies(word, wordCursor, nextRow, nextColumn, board_);	//recurse
				if((!retval)){--wordCursor;}							//move wordCursor back if word not found
                		board_[row][column] = actualLetter;						//change the spot on the board back
                	}
                	++j;											
                }
                ++i;
		j = -1;
        }
	if(wordCursor == word.size())										//if we've reached the last spot in the word
	{
		retval = true;											//then we found the word
	}
	return retval;
}

//copys board
void BoggleBoard::copy(const BoggleBoard& rhs)
{
	if(&rhs != this)
	{
		for(int i = 0;i < width_;++i)			//go through every square on the board
		{
			for(int j = 0;j < width_;++j)
			{
				board_[i][j] = rhs.board_[i][j];//and copy that letter
			}
		}
	}	
}

//adds letters to the board
void BoggleBoard::construct(BogglePieceGenerator& gen)
{
	for(int j = 0; j < width_;j++)
	{
		for(int i = 0; i < width_;i++)
		{
			board_[j][i] = tolower(gen.getNextChar());//set each spot on the board equal to the generated letter
		}
	}
}

//creates the board
void BoggleBoard::normalize()
{
	board_ = new char*[width_];
        for(int i = 0;i < width_;++i)
        {
                board_[i] = new char[width_];
        }
}
