#include "ConsoleInterface.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;


ConsoleInterface::ConsoleInterface(void){
  // nothing yet
}


ConsoleInterface::~ConsoleInterface(void){
  // nothing yet
}


void ConsoleInterface::printBoard(BoggleBoard& board){
  printRow(board, 0);
  int maxRows = board.getWidth();
  for(int i = 1; i < maxRows; i++){
    printCrossBar(board);		
    printRow(board, i);
  }

}


void ConsoleInterface::printCrossBar(BoggleBoard& board){
  int maxColumns = board.getWidth();
  for(int i = 0; i < maxColumns; i++){
    cout << "----";
  }
  cout << endl;
}

void ConsoleInterface::printRow(BoggleBoard& board, int row){
  int maxRows = board.getWidth();
  cout << " " << board.getLetter(row,0) << " ";
  for(int i = 1; i < maxRows; i++){
    cout << "|";
    cout << " " << board.getLetter(row,i) << " ";
  }
  cout << endl;
}


/*
 * Read in player words.  Does not check if they are valid or have been played before.
 * Returns true if the human player submitted a word.
 */
bool ConsoleInterface::readNextMove(string& word){

  string line;
  // parse the string
  int count = 0;
  do{
    cout << "Input a word or press <ENTER>" << endl;

    // read in a line
    getline(cin, line);

    // bind it to string stream for more parsing
    istringstream input(line);

    // parse the line, counting the number of words that come out
    count = 0;
    while( input >> word ){
      count++;
    }

    if( count > 1 ){
      cout << "Invalid word: Use single words only (no spaces)" << endl;
    }
  }while( count > 1); // keep asking until they enter one or none words

  return count != 0;
}

bool ConsoleInterface::playAnotherGame(){
  string line;
  char response;

  do{
    cout << "Would you like to play again (Y/N)?" << endl;

    // read the line
    getline(cin, line);

    // bind it to string stream for more parsing
    istringstream input(line);
    input >> response;
    response = toupper(response);
  }while( response != 'Y' && response != 'N' );

  return response == 'Y';
}



void ConsoleInterface::printScore(int humanScore, int computerScore){

  cout << "You: " << humanScore << " Me: " << computerScore << endl;
  if( humanScore > computerScore ){
    cout << "You win. Probably because you cheated." << endl;
  }
  else if( computerScore > humanScore ){
    cout << "I win. Again." << endl;
  }
  else{
    cout << "A draw.  Everybody loses." << endl;
  }
  cout << endl;

}
