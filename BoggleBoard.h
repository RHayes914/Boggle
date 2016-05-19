//Ryan Hayes
//Spring 2016
//Boggle Board Class

#ifndef BOGGLE_BOARD_H
#define BOGGLE_BOARD_H

#include "BogglePieceGenerator.h"
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

class BoggleBoard
{
public:

	// methods

	/*
	 * Creates a board of the given size.  Fills the board with characters from the RandomCharacterGenerator.
	 * The board should be filled from left to right and top to bottom, e.g, 
	 *   1  2  3  4
	 *   5  6  7  8
	 *   9 10 11 12
	 *  13 14 15 16
	 */
	BoggleBoard(int width, BogglePieceGenerator& gen);
	virtual ~BoggleBoard(void);
	BoggleBoard(const BoggleBoard& rhs);
	BoggleBoard& operator =(const BoggleBoard& rhs);

	/*
	 * returns the character found on the board at this location
	 */
	char getLetter(int row,int column);
	int getWidth();

	/*
	 * returns true if this word is found on the board
	 */
	bool isWordOnBoard(string word);

	/*sets spot on board to certain letter*/
	void setLetter(char letter, int row, int column);
private:
	//create new board
	void normalize();
	//copy a board	
	void copy(const BoggleBoard& rhs);
	//fill board with letters
	void construct(BogglePieceGenerator& gen);
	//helper function for isWordOnBoard that finds adjacent squares
	bool findAdjacencies(string word, int wordCursor, int row, int column, char**& board);
private:
	char** board_;
private:
	int width_;
};

#endif
