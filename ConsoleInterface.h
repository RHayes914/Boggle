#ifndef CONSOLE_INTERFACE_H
#define CONSOLE_INTERFACE_H

#include "BoggleBoard.h"
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

class ConsoleInterface
{


 public:
  ConsoleInterface(void);
  virtual ~ConsoleInterface(void);
  // prints Boggle Board to the console
  void printBoard(BoggleBoard&);
  /*
   * Read in player words.  Does not check if they are valid or have been played before.
   * Only checks whether they enter 1 string with no spaces.
   * Returns true if the human player submitted a word.
   */
  bool readNextMove(string&);
  // asks the user if they want to play another game
  bool playAnotherGame();
  // prints the scores to the console
  void printScore(int humanScore, int computerScore);

  // writes the strings from begin to end to a log file called "<logPrefix>.<playCount>.txt"
  template <class InputIterator>
    void logWords(InputIterator begin, InputIterator end, string logPrefix, int playCount){
    stringstream ss;
    string fileName;
    ss << logPrefix << playCount << ".txt";
    ss >> fileName;
    
    // open the file
    ofstream outStream(fileName.c_str());
    if( outStream.fail() ){
      cerr << "Failed to open " << fileName << endl;
      exit(1);
    }
    
    // write the words
    while(begin != end){
      outStream << *begin << endl;
      begin++;
    }
    
    // close the file
    outStream.close();
  }

 private:

  // methods
  // prints a crossbar to the console
  void printCrossBar(BoggleBoard&);
  // prints the given row
  void printRow(BoggleBoard&, int);
	
};

#endif // CONSOLE_INTERFACE_H
