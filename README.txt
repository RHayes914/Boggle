/*
	This is a text based version of Boggle.

	Boggle is a word game in which a player finds the words on a grid of 
	letters (at least two letters in length) by tracing a path through adjacent letters.
	The same letter may not be used twice. The goal of the game is to find all words on the
	board. This version of Boggle is not timed.

	When run in the shell, the program may take 0 or 4 command line arguements:

	1. The board size (3 or more)
	2. The seed to random boggle piece generator (changing this value changes the board).
	3. The minimum length for a valid word (two or more).
	4. The name of the lexicon file.
	
	For example: ./boggle 7 43 5 pigLatinDictionary.txt

	Otherwise, when 0 command line arguments are entered, they default to:

	1. The board is size 4x4.
	2. The seed is 7.
	3. The minimum length for a word is three.
	4. The lexicon is found in lexicon.txt. (provided)

	After the Human Player has finished playing, they will enter a blank line.
	The computer will then find all words on the board that have not been found by the human.
	
	After each game the words the user found are saved in a log file human<N>.txt where <N> is the game number.
	The words that the computer found are saved in comp<N>.txt. 

*/