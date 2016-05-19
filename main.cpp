/*#include "Lexicon.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	Lexicon l("lexicon.txt");
	
	std::string word = "";
	do{
		std::cout << "Enter your word: ";
		std::cin >> word;
		std::cout << Lexicon::toWord(l.wordStatus(word)) << std::endl;
	}while(word[0] >= 'a' && word[0] <= 'z');
        return 0;
}*/

#include "ConsoleInterface.h"
#include "ComputerPlayer.h"
#include "Lexicon.h"
#include "BogglePieceGenerator.h"
#include <iostream>
#include <string>
#include <fstream>
#include <set>

int main(int argc, char* argv[]){
  int boardSize = 4; //default board
  int rseed = 7;
  int minLetters = 3;
  string lexiconFile = "lexicon.txt";

  /*int boardSize = 5; //nope board
  int rseed = 12;
  int minLetters = 3;
  string lexiconFile = "lexicon.txt";*/

  /*int boardSize = 10; //hoax board
  int rseed = 500;
  int minLetters = 3;
  string lexiconFile = "lexicon.txt";*/


  if(argc != 5 && argc != 1){
    cerr << "Incorrect number of command line arguments" << endl;
    exit(1);
  }

  if( argc == 5 ){
    boardSize = atoi(argv[1]);
    rseed = atoi(argv[2]);
    minLetters = atoi(argv[3]);
    lexiconFile = string(argv[4]);
  }

  // check the arguments passed in
  ifstream testStream(lexiconFile.c_str());
  if( boardSize < 3 || rseed == 0 ||	minLetters < 2 || testStream.fail() ){
    cerr << "Invalid arguments" << endl;
    exit(1);
  }
  testStream.close();

  // make the random character generator
  BogglePieceGenerator charGen(boardSize*boardSize, rseed);

  // make the console interface
  ConsoleInterface console;

  // make the lexicon file
  Lexicon lexicon(lexiconFile);

  // make the computer player
  ComputerPlayer computer(lexicon);

  // make the log file prefixes
  string humanFilePrefix = "human";
  string computerFilePrefix = "comp";

  set<string> humanWords;
  set<string> compWords;

  int playCount = 0;
  bool wannaPlay = true;
  while( wannaPlay ){
    playCount++;
    compWords.clear();
    humanWords.clear();
    // make the board
    BoggleBoard board(boardSize, charGen);

    // print the initial board
    console.printBoard(board);
    cout << endl;
	
    /* STUDENT SECTION */

    // get human player words
	
    string humanPlayerWord;
    while(console.readNextMove(humanPlayerWord)) {
	Lexicon::lowerCaseConvert(humanPlayerWord);
    	if(humanPlayerWord.size() < minLetters) //check to see if the word is the correct length
      	{
		cout << "Please enter a word of at least " << minLetters << " letters. " << endl;
      	}
	else if(lexicon.wordStatus(humanPlayerWord) != 1) //check to see if the string is an actual word
	{
		cout << "Please enter an actual word (feel free to consult the scrabble dictionary). " << endl;
	}
	else if(!board.isWordOnBoard(humanPlayerWord))//check to see whether the word is on the board
	{
		cout << "That word is not on the board! " << endl;
	}
	else if(humanWords.count(humanPlayerWord) > 0)//check to see whether it has been played before
	{
		cout << "That word has already been played! " << endl;
	}
	else
	{
		humanWords.insert(humanPlayerWord);
	}
    }

    int humanScore = humanWords.size();
    cout << "Your score is: " << humanScore << endl;
     
     // log the human player's words
    console.logWords(humanWords.begin(), humanWords.end(), humanFilePrefix, playCount);
    
    // ask computer player for words
    cout << endl << "Thinking..." << endl << endl;;
    compWords = computer.playBoggle(minLetters, board, humanWords);
    int computerScore = compWords.size();
    cout << "The computer score is: " << computerScore << endl;
    // log the computer player's words
    console.logWords(compWords.begin(), compWords.end(), computerFilePrefix, playCount);

    // print score
    console.printScore(humanScore, computerScore);

    /* END STUDENT SECTION */

    wannaPlay = console.playAnotherGame();
  }
}


